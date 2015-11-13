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

add_library(
  nodejs-static
  config.h
)

set_target_properties(
  nodejs-static PROPERTIES
  LINKER_LANGUAGE CXX
)

target_link_libraries(
  nodejs-static

  -Wl,--whole-archive node -Wl,--no-whole-archive
  uv
  cares
  openssl
  zlib
  http_parser

  v8_libplatform
  v8_base
  v8_libbase
  v8_nosnapshot

  pthread
  dl
)

if(cmake_build_type_tolower STREQUAL "debug")
  add_custom_command(
    TARGET nodejs-static PRE_LINK
    COMMAND ${CMAKE_SOURCE_DIR}/deps/build-debug.sh
  )
else()
  add_custom_command(
    TARGET nodejs-static PRE_LINK
    COMMAND ${CMAKE_SOURCE_DIR}/deps/build.sh
  )
endif()
