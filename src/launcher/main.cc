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

#include <boost/filesystem.hpp>

void usage() {
  std::cout << "Usage: "
            << executable_name()
            << " "
            << "<path-to-scope-ini>"
            << " "
            << "[<path-to-runtime-ini>]"
            << std::endl;
}

int main(int argc, char *argv[]) {
  if (argc < 2 || argc > 3) {
    usage();
    return EXIT_FAILURE;
  }

  std::string ini_filename = argv[1];

  if (ini_filename.empty()
      || !boost::filesystem::exists(ini_filename)) {
    std::cout << "Invalid or non existant scope ini file name: "
              << ini_filename << std::endl;
    usage();
    return EXIT_FAILURE;
  }

  boost::filesystem::path p(ini_filename);

  if (p.extension().string() != ".ini") {
    std::cout << "Invalid scope ini file name extension: "
              << ini_filename << std::endl;
    return EXIT_FAILURE;
  }

  setenv(kJavascriptUnityScopeIdEnvVarName,
         p.string().c_str(),
         true);

  if (argc == 3 && !std::string(argv[2]).empty()) {
      std::string runtime_filename = argv[2];

      if (!boost::filesystem::exists(runtime_filename)) {
        std::cout << "Non-existant runtime ini file: "
                  << runtime_filename << std::endl;
        usage();
        return EXIT_FAILURE;
      }

      boost::filesystem::path p(runtime_filename);

      if (p.extension().string() != ".ini") {
        std::cout << "Invalid runtime ini file name extension: "
                  << runtime_filename << std::endl;
        return EXIT_FAILURE;
      }

      setenv(kJavascriptUnityRuntimeEnvVarName,
             p.string().c_str(),
             true);
  }

  std::string base_name = p.filename().string();

  boost::filesystem::path script_path = p.parent_path();
  script_path += std::string("/") + p.stem().string() + ".js";

  if (!boost::filesystem::exists(script_path)) {
    std::cout << "Could not find scope javascript file: "
              << script_path.string() << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<std::string::value_type>
    new_args_content(
      executable_name().size() + 1
      + script_path.string().size() + 1);

  memcpy(&new_args_content[0],
         executable_name().c_str(),
         executable_name().size()+1);

  memcpy(&new_args_content[0]
         + executable_name().size()
          + 1,
         script_path.string().c_str(),
         script_path.string().size()+1);

  std::vector<std::string::value_type*>
    new_args;
  new_args.push_back(&new_args_content[0]);
  new_args.push_back(&new_args_content[0] + executable_name().size() + 1);

  return node::Start(
      new_args.size(),
      &new_args[0]);
}
