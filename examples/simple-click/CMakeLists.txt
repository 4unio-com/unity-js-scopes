project(js-scope)
cmake_minimum_required(VERSION 2.8.10)

# Do not remove this, its required to ensure the correct node binaries are included in the project
message(STATUS "Retrieving scopes bindings")

execute_process(
  COMMAND cp -r --parents /node_modules/unity-js-scopes ${CMAKE_SOURCE_DIR}/src
  RESULT_VARIABLE _BINDINGS_RESULT
  )

if(NOT _BINDINGS_RESULT EQUAL 0)
  message(FATAL_ERROR "Retrieving scopes bindings failed")
endif()

# Do not remove this, its required for the correct functionality of the Ubuntu-SDK
set(UBUNTU_MANIFEST_PATH "manifest.json.in" CACHE INTERNAL "Tells QtCreator location and name of the manifest file")
set(UBUNTU_PROJECT_TYPE "Scope" CACHE INTERNAL "Tells QtCreator this is a Scope project")

# Important project paths
set(CMAKE_INSTALL_PREFIX /)
set(SCOPE_INSTALL_DIR "/js-scope")
set(GETTEXT_PACKAGE "js-scope")
set(PACKAGE_NAME "js-scope.webapps")
set(SCOPE_NAME "${PACKAGE_NAME}_js-scope")

# This command figures out the target architecture and puts it into the manifest file
execute_process(
  COMMAND dpkg-architecture -qDEB_HOST_ARCH
  OUTPUT_VARIABLE CLICK_ARCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(manifest.json.in ${CMAKE_CURRENT_BINARY_DIR}/manifest.json)

# Install the click manifest
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/manifest.json DESTINATION "/")
install(FILES "js-scope.apparmor" DESTINATION "/")

# Make these files show up in QtCreator
add_custom_target(hidden_files
  ALL
  SOURCES
    manifest.json.in
    js-scope.apparmor
)

# Add our main directories
add_subdirectory(data)
add_subdirectory(src)
