/*
 * Copyright 2015 Canonical Ltd.
 *
 * This file is part of unity-js-scopes.
 *
 * unity-js-scopes is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * unity-js-scopes is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include "node.h"

#include "../common/config.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

std::string get_arch() {
  std::string result = "";

  {
    FILE* pipe = popen("dpkg-architecture -qDEB_HOST_ARCH", "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    while (!feof(pipe)) {
      if (fgets(buffer, 128, pipe) != NULL)
        result += buffer;
    }
    result.pop_back();
    pclose(pipe);
  }

  result += "-";

  {
    FILE* pipe = popen("lsb_release -rs", "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    while (!feof(pipe)) {
      if (fgets(buffer, 128, pipe) != NULL)
        result += buffer;
    }
    result.pop_back();
    pclose(pipe);
  }

  return result;
}

void usage() {
  std::cout << "Usage:"
            << std::endl
            << executable_name()
            << " [re]install "
            << "<path/to/node_modules> "
            << "[<npm_module>]"
            << std::endl
            << executable_name()
            << " [re]build "
            << "<path/to/node_modules> "
            << std::endl;
}

void install_unity_js_scopes(std::string const& modules_dir)
{
  // Remove any existing unity-js-scopes bindings from the target directory
  if (boost::filesystem::exists(modules_dir + "/unity-js-scopes")) {
    std::cout << "Removing '" << modules_dir << "/unity-js-scopes' ..." << std::endl;
    boost::filesystem::remove_all(modules_dir + "/unity-js-scopes");
  }

  // Copy the unity-js-scopes bindings into the target directory
  std::cout << "Copying '/node_modules/unity-js-scopes' to '" << modules_dir << "' ..." << std::endl;
  boost::filesystem::create_directory(modules_dir + "/unity-js-scopes");
  boost::filesystem::copy("/node_modules/unity-js-scopes/index.js",
                          modules_dir + "/unity-js-scopes/index.js");
  boost::filesystem::copy("/node_modules/unity-js-scopes/unity_js_scopes_bindings.node",
                          modules_dir + "/unity-js-scopes/unity_js_scopes_bindings.node");

  boost::filesystem::create_directory(modules_dir + "/unity-js-scopes/lib");
  boost::filesystem::copy("/node_modules/unity-js-scopes/lib/scope-core.js",
                          modules_dir + "/unity-js-scopes/lib/scope-core.js");

  std::cout << "Copying '/usr/bin/unity-js-scopes-launcher' to '" << modules_dir << "/unity-js-scopes/bin' ..." << std::endl;
  boost::filesystem::create_directory(modules_dir + "/unity-js-scopes/bin");
  boost::filesystem::copy("/usr/bin/unity-js-scopes-launcher",
                          modules_dir + "/unity-js-scopes/bin/unity-js-scopes-launcher");
}

int main(int argc, char *argv[]) {
  if (argc < 2 || std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
    usage();
    return EXIT_FAILURE;
  }

  if (std::string(argv[1]) == "install" ||
      std::string(argv[1]) == "reinstall" ||
      std::string(argv[1]) == "build" ||
      std::string(argv[1]) == "rebuild") {
    if (argc < 3) {
      usage();
      return EXIT_FAILURE;
    }

    int result = EXIT_FAILURE;
    std::string modules_dir = argv[2];

    /// ERROR CHECKS
    /// ============

    // Check that the target path is not empty
    if (modules_dir.empty()) {
      std::cout << "Target path can not be empty"
                << std::endl;
      usage();
      return EXIT_FAILURE;
    }

    // If the target path exists, check that it is a directory
    if (boost::filesystem::exists(modules_dir)
        && !boost::filesystem::is_directory(modules_dir)) {
      std::cout << "'" << modules_dir << "' is not a directory"
                << std::endl;
      usage();
      return EXIT_FAILURE;
    }

    // Check that the target directory is named "node_modules"
    if (!boost::algorithm::ends_with(modules_dir, "node_modules")
        && !boost::algorithm::ends_with(modules_dir, "node_modules/")) {
      std::cout << "Target directory should be named 'node_modules'"
                << std::endl;
      usage();
      return EXIT_FAILURE;
    }

    /// INITIALISE
    /// ==========

    std::cout << "Installation started." << std::endl;

    // Ensure that the target directory exists
    if (!boost::filesystem::exists(modules_dir)) {
      std::cout << "Creating '" << modules_dir << "' ..." << std::endl;
      boost::filesystem::create_directories(modules_dir);
    }

    // Create symlinks for node and node-gyp
    boost::filesystem::remove(modules_dir + "/node");
    boost::filesystem::remove(modules_dir + "/node-gyp");

    std::cout << "Creating '" << modules_dir << "/node' symlink ..." << std::endl;
    boost::filesystem::create_symlink("/usr/bin/unity-js-scopes-tool",
                                      modules_dir + "/node");

    std::cout << "Creating '" << modules_dir << "/node-gyp' symlink ..." << std::endl;
    boost::filesystem::create_symlink("/node_modules/npm/bin/node-gyp-bin/node-gyp",
                                      modules_dir + "/node-gyp");

    std::string abs_modules_dir = boost::filesystem::absolute(boost::filesystem::path(modules_dir)).native();
    std::string path_env = "PATH=" + abs_modules_dir + ":" + getenv("PATH");
    std::cout << "Setting '" << path_env << "' ..." << std::endl;
    putenv(const_cast<char*>(path_env.c_str()));

    /// INSTALL
    /// =======

    // Determine whether we are installing unity-js-scopes or an npm module
    if (boost::algorithm::ends_with(std::string(argv[1]), "install") && argc > 3
        && std::string(argv[3]) != "unity-js-scopes") // Install an npm module
    {
      std::string npm_module = argv[3];

      // Don't reinstall an already installed module unless "reinstall" is called
      if (std::string(argv[1]) == "reinstall" || !boost::filesystem::exists(modules_dir + "/" + npm_module))
      {
        // A new npm module has been installed, we need to reset our should_build flag
        if (boost::filesystem::exists(modules_dir + "/last-build-arch.txt"))
        {
          boost::filesystem::remove(modules_dir + "/last-build-arch.txt");
        }

        // Install the npm module
        std::cout << "Installing npm module '" << npm_module << "' to '" << modules_dir << "' ..." << std::endl;

        std::string node_cmd = "node /node_modules/npm/cli.js --prefix='" + modules_dir + "/../' --ignore-scripts install " + npm_module;
        std::cout << "Running '" << node_cmd << "' ..." << std::endl;
        result = system(node_cmd.c_str());
      }
      else
      {
        result = EXIT_SUCCESS;
      }
    }
    else if (std::string(argv[1]) == "reinstall" || !boost::filesystem::exists(modules_dir + "/unity-js-scopes")) // Install the unity-js-scopes module
    {
      install_unity_js_scopes(modules_dir);
    }

    /// REBUILD
    /// =======

    // A rebuild has been forced, we need to reset our should_build flag
    if (std::string(argv[1]) == "rebuild" && boost::filesystem::exists(modules_dir + "/last-build-arch.txt"))
    {
      boost::filesystem::remove(modules_dir + "/last-build-arch.txt");
    }

    /// BUILD
    /// =====

    // Handle 'unity-js-scopes build' and 'unity-js-scopes rebuild' now
    if (boost::algorithm::ends_with(std::string(argv[1]), "build"))
    {
      bool should_build = true;
      std::string current_arch = get_arch();

      // Check if we have built for this arch already, if so set should_build to false
      if (boost::filesystem::exists(modules_dir + "/last-build-arch.txt"))
      {
        std::ifstream in(modules_dir + "/last-build-arch.txt");
        std::string last_arch;
        in >> last_arch;
        in.close();
        if (last_arch == current_arch)
        {
          should_build = false;
        }
      }

      if (should_build)
      {
        std::vector<std::string> environment_updates;
        
        std::cout << "Setting target arch to '" << current_arch << "' ..." << std::endl;
        if (boost::algorithm::starts_with(current_arch, "armhf"))
        {
          if (boost::filesystem::exists("/usr/bin/arm-linux-gnueabihf-gcc-5"))
          {
            std::cout << "Setting armhf compiler to 'GCC 5' ..." << std::endl;
            environment_updates.push_back("CC=arm-linux-gnueabihf-gcc-5");
            environment_updates.push_back("CXX=arm-linux-gnueabihf-g++-5");
            environment_updates.push_back("LINK=arm-linux-gnueabihf-g++-5");
            environment_updates.push_back("AR=arm-linux-gnueabihf-ar");
            environment_updates.push_back("npm_config_arch=arm");
          }
          else if (boost::filesystem::exists("/usr/bin/arm-linux-gnueabihf-gcc-4.9"))
          {
            std::cout << "Setting armhf compiler to 'GCC 4.9' ..." << std::endl;
            environment_updates.push_back("CC=arm-linux-gnueabihf-gcc-4.9");
            environment_updates.push_back("CXX=arm-linux-gnueabihf-g++-4.9");
            environment_updates.push_back("LINK=arm-linux-gnueabihf-g++-4.9");
            environment_updates.push_back("AR=arm-linux-gnueabihf-ar");
            environment_updates.push_back("npm_config_arch=arm");
          }
          else
          {
            std::cout << "WARNING: No armhf compiler found. Using system default." << std::endl;
          }
        }

        for (auto e: environment_updates) {
          putenv(const_cast<char*>(e.c_str()));
        }
        
        // Reinstall the unity-js-scopes module for new target arch
        install_unity_js_scopes(modules_dir);

        // Build any binary npm modules for the current targeted arch
        std::cout << "Building binary modules in '" << modules_dir << "' ..." << std::endl;

        std::string node_cmd = "node /node_modules/npm/cli.js --prefix='" + modules_dir + "/../' rebuild";
        std::cout << "Running '" << node_cmd << "' ..." << std::endl;
        result = system(node_cmd.c_str());

        if (result == EXIT_SUCCESS)
        {
          // Write the current arch to file so that we can compare with it on the next build
          std::ofstream out(modules_dir + "/last-build-arch.txt");
          out << current_arch;
          out.close();
        }
      }
      else
      {
        result = EXIT_SUCCESS;
      }
    }
    else
    {
      result = EXIT_SUCCESS;
    }

    /// FINALISE
    /// ========

    // Cleanup symlinks
    std::cout << "Cleaning up symlinks ..." << std::endl;
    boost::filesystem::remove(modules_dir + "/node");
    boost::filesystem::remove(modules_dir + "/node-gyp");

    if (result == EXIT_SUCCESS)
    {
      std::cout << "Installation complete." << std::endl;
    }
    else
    {
      std::cout << "Installation failed." << std::endl;
    }

    return result;
  }
  else {
    return node::Start(argc, argv);
  }
}
