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
#include <cstdlib>
#include <cstring>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

void usage() {
  std::cout << "Usage: "
            << std::endl
            << executable_name()
            << " install "
            << "<path/to/node_modules> "
            << "[<npm_module>]"
            << std::endl
            << executable_name()
            << " rebuild "
            << "<path/to/node_modules> "
            << "[<target_arch>]"
            << std::endl;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    usage();
    return EXIT_FAILURE;
  }

  if (std::string(argv[1]) == "install" || std::string(argv[1]) == "rebuild") {
    if (argc < 3) {
      usage();
      return EXIT_FAILURE;
    }

    int result = EXIT_FAILURE;
    std::string modules_dir = argv[2];

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

    // Determine whether we are installing unity-js-scopes or an npm module
    if (std::string(argv[1]) == "install" && argc > 3
        && std::string(argv[3]) != "unity-js-scopes") // Install an npm module
    {
      std::string npm_module = argv[3];

      // Install the npm module
      std::cout << "Installing npm module '" << npm_module << "' to '" << modules_dir << "' ..." << std::endl;

      std::string node_cmd = "node /node_modules/npm/cli.js --prefix='" + modules_dir + "/../' install " + npm_module;
      std::cout << "Running '" << node_cmd << "' ..." << std::endl;
      result = system(node_cmd.c_str());
    }
    else // Install the unity-js-scopes module
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

    // Handle 'unity-js-scopes rebuild'
    if (std::string(argv[1]) == "rebuild")
    {
      if (argc > 3)
      {
        std::cout << "Setting target arch to '" << std::string(argv[3]) << "' ..." << std::endl;
        if (std::string(argv[3]) == "armhf")
        {
          if (boost::filesystem::exists("/usr/bin/arm-linux-gnueabihf-gcc-5"))
          {
            std::cout << "Setting armhf compiler to 'GCC 5' ..." << std::endl;
            putenv("CC=arm-linux-gnueabihf-gcc-5");
            putenv("CXX=arm-linux-gnueabihf-g++-5");
            putenv("LINK=arm-linux-gnueabihf-g++-5");
            putenv("AR=arm-linux-gnueabihf-ar");
            putenv("npm_config_arch=arm");
          }
          else if (boost::filesystem::exists("/usr/bin/arm-linux-gnueabihf-gcc-4.9"))
          {
            std::cout << "Setting armhf compiler to 'GCC 4.9' ..." << std::endl;
            putenv("CC=arm-linux-gnueabihf-gcc-4.9");
            putenv("CXX=arm-linux-gnueabihf-g++-4.9");
            putenv("LINK=arm-linux-gnueabihf-g++-4.9");
            putenv("AR=arm-linux-gnueabihf-ar");
            putenv("npm_config_arch=arm");
          }
          else
          {
            std::cout << "WARNING: No armhf compiler found. Using system default." << std::endl;
          }
        }
      }

      // Rebuild any binary npm modules for the current targeted arch
      std::cout << "Rebuilding binary modules in '" << modules_dir << "' ..." << std::endl;

      std::string node_cmd = "node /node_modules/npm/cli.js --prefix='" + modules_dir + "/../' rebuild";
      std::cout << "Running '" << node_cmd << "' ..." << std::endl;
      result = system(node_cmd.c_str());
    }
    else
    {
      result = EXIT_SUCCESS;
    }

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
