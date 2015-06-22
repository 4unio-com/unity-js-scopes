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
)

link_directories(
  ${NODE_DEPS_LIB_DIRS}
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
  net-cpp>=1.1.0
  REQUIRED
)

include_directories(
  "${CMAKE_SOURCE_DIR}/include"
  ${Boost_INCLUDE_DIRS}
  ${SCOPE_INCLUDE_DIRS}
  )

target_link_libraries(
  ${SCOPE_NODEJS_ADDON_BIN_NAME}

  ${SCOPE_LIBRARIES}

  icui18n
  icuuc
  icudata

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
  ${SCOPE_NODEJS_ADDON_BIN_NAME}.node
  )

install(DIRECTORY .
  DESTINATION /node_modules/unity-js-scopes
  FILES_MATCHING PATTERN "*.js"
  PATTERN "src" EXCLUDE
  PATTERN "CMakeFiles" EXCLUDE)

install(FILES ${ADDON_BINARY_FILES}
        DESTINATION /node_modules/unity-js-scopes)
