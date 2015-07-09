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
)

link_directories(
  ${Boost_LIB_DIRS}
)

set(EXECUTABLE_NAME unity-js-scopes-launcher)

add_executable(
    ${EXECUTABLE_NAME}
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
  ${EXECUTABLE_NAME}

  -Wl,--whole-archive iojs -Wl,--no-whole-archive
  uv
  cares
  openssl
  zlib
  http_parser

  v8_base
  v8_libbase
  v8_libplatform
  v8_nosnapshot

  ${Boost_LIBRARIES}

  icui18n
  icuuc
  icudata
  
  pthread
  dl
  )

install(TARGETS ${EXECUTABLE_NAME}
        RUNTIME DESTINATION /usr/bin)
