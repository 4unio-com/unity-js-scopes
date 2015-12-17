# vim:expandtab:shiftwidth=2:tabstop=2:

# Copyright (C) 2015 Canonical Ltd.

# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.

# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

cmake_minimum_required(VERSION 2.8.11)

project(js-scopes)

# Retrieve dependencies

message(STATUS "Retrieving deps")

execute_process(
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/deps/get.sh
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  RESULT_VARIABLE _DEPS_RESULT
  )

if(NOT _DEPS_RESULT EQUAL 0)
  message(FATAL_ERROR "Retriving deps failed")
endif()

# Configure CMake environment

string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_lower)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE CACHE INTERNAL "")

if(cmake_build_type_lower MATCHES coverage)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -g")
    set(CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} --coverage -g")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} --coverage -g")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -g")
endif()

include(CheckCXXCompilerFlag)
include(CheckIncludeFileCXX)
include(EnableCoverageReport)
include(GNUInstallDirs)

# Add includes

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/node.js/deps/uv/include
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/node.js/deps/v8/include
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/node.js/src
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/v8-cpp/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  )

if(cmake_build_type_lower MATCHES debug)
  link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/node.js/out/Debug
  )
else()
  link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/node.js/out/Release
  )
endif()

# Add sources

enable_testing()

add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(tests)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples
        DESTINATION ${CMAKE_INSTALL_DATADIR}/unity-js-scopes)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/qtc-templates/scope-js
        DESTINATION /usr/share/qtcreator/templates/wizards/ubuntu)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/qtc-templates/scope-js
        DESTINATION /usr/ubuntu-sdk-ide/share/qtcreator/templates/wizards/ubuntu)


add_custom_target(
  check
  ${CMAKE_CTEST_COMMAND} --force-new-ctest-process --output-on-failure
)

# Enable coverage report

if (cmake_build_type_lower MATCHES coverage)
  ENABLE_COVERAGE_REPORT(TARGETS unity_js_scopes_bindings
                         FILTER /usr/include
                                ${CMAKE_CURRENT_SOURCE_DIR}/deps/*
                                ${CMAKE_CURRENT_SOURCE_DIR}/examples/*
                                ${CMAKE_CURRENT_SOURCE_DIR}/qtc-templates/*
                                ${CMAKE_CURRENT_SOURCE_DIR}/tests/*
                                ${CMAKE_BINARY_DIR}/*)
endif()
