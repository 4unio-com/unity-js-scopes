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

project(scopes-binding CXX)

file(
    GLOB
    SRC_FILES
    ./src/*.h
    ./src/*.cc
    ./lib/*.js
    )

add_definitions(
    -std=c++11
    -fno-permissive
    -pedantic
    -Wall
    -Wextra
    -fPIC
    -Wno-unused-parameter
    )

link_directories(
  ${SCOPE_LIB_DIRS}
  )

set(SCOPE_NODEJS_ADDON_BIN_NAME
  unity_js_scopes_bindings
  )

add_library(
    ${SCOPE_NODEJS_ADDON_BIN_NAME} SHARED
    ${SRC_FILES}
    )

find_package(PkgConfig)

find_package(
  Boost
  REQUIRED
  )

pkg_check_modules(
  SCOPE
  libunity-scopes>=0.6.0
  REQUIRED
  )

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${SCOPE_INCLUDE_DIRS}
  )

target_link_libraries(
  ${SCOPE_NODEJS_ADDON_BIN_NAME}

  ${SCOPE_LIBRARIES}

  pthread
  dl
  )

set_target_properties(
  ${SCOPE_NODEJS_ADDON_BIN_NAME}
  PROPERTIES
  PREFIX ""
  SUFFIX ".node"
  )

set(ADDON_BINARY_FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${SCOPE_NODEJS_ADDON_BIN_NAME}.node
  )

add_custom_command(
  TARGET ${SCOPE_NODEJS_ADDON_BIN_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
    "${CMAKE_BINARY_DIR}/tests/node_modules/unity-js-scopes/lib"

  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_BINARY_DIR}/unity_js_scopes_bindings.node"
    "${CMAKE_BINARY_DIR}/tests/node_modules/unity-js-scopes"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/index.js"
    "${CMAKE_BINARY_DIR}/tests/node_modules/unity-js-scopes"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/scope-core.js"
    "${CMAKE_BINARY_DIR}/tests/node_modules/unity-js-scopes/lib"
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/deps/node.js/deps/npm
  DESTINATION /node_modules
  USE_SOURCE_PERMISSIONS
  )

install(DIRECTORY .
  DESTINATION /node_modules/unity-js-scopes
  FILES_MATCHING PATTERN "*.js"
  PATTERN "src" EXCLUDE
  PATTERN "CMakeFiles" EXCLUDE
  )

install(FILES ${ADDON_BINARY_FILES}
  DESTINATION /node_modules/unity-js-scopes
  )
