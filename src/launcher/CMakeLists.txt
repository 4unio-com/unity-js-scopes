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

project(unity-js-scopes-launcher CXX)

file(
    GLOB
    SRC_FILES
    ./*.h
    ./*.cc
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
  ${Boost_LIB_DIRS}
)

set(LAUNCHER_EXECUTABLE_NAME unity-js-scopes-launcher)

configure_file(
    config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
    @ONLY)

add_executable(
    ${LAUNCHER_EXECUTABLE_NAME}
    ${SRC_FILES}
    )

find_package(PkgConfig)
find_package(Boost
  COMPONENTS system filesystem
  REQUIRED)

include_directories(
  ${Boost_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/include"
  ${SCOPE_INCLUDE_DIRS}
  )

target_link_libraries(
  ${LAUNCHER_EXECUTABLE_NAME}
  nodejs-static
  ${Boost_LIBRARIES}
  )

add_custom_command(
  TARGET ${LAUNCHER_EXECUTABLE_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
    "${CMAKE_BINARY_DIR}/tests/node_modules/unity-js-scopes/bin"

  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_BINARY_DIR}/unity-js-scopes-launcher"
    "${CMAKE_BINARY_DIR}/tests/node_modules/unity-js-scopes/bin"
)

install(TARGETS ${LAUNCHER_EXECUTABLE_NAME}
        RUNTIME DESTINATION /usr/bin)
