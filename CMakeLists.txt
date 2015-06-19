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

include(CheckCXXCompilerFlag)
include(CheckIncludeFileCXX)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE CACHE INTERNAL "")

message(STATUS "Retrieving deps")

execute_process(
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/deps/get.sh
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  RESULT_VARIABLE _DEPS_RESULT
  )

if(NOT _DEPS_RESULT EQUAL 0)
  message(FATAL_ERROR "Retriving deps failed")
endif()

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/v8-cpp/cmake
  )

find_package(Node REQUIRED)

include_directories(
  ${NODE_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/v8-cpp/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  )

add_custom_target(
  deps
  COMMAND
  ${CMAKE_CURRENT_SOURCE_DIR}/deps/build.sh
  )

add_subdirectory(src)
