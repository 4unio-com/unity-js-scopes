project(js-scope)
cmake_minimum_required(VERSION 2.8.10)

# Do not remove this, its required to ensure the correct node binaries are included in the project
set(CONFIG_CMD /node_modules/unity-js-scopes/bin/unity-js-scopes-configure)
execute_process(COMMAND ${CONFIG_CMD} ${CMAKE_SOURCE_DIR}/src/node_modules)
add_custom_target(rebuild_npm_modules ALL COMMAND ${CONFIG_CMD} ${CMAKE_SOURCE_DIR}/src/node_modules)

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

# Install the manifest and apparmor files
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/manifest.json DESTINATION "/")
install(FILES "js-scope.apparmor" DESTINATION "/")

# Make manifest, apparmor, and js files show up in QtCreator
file(GLOB_RECURSE
  _JS_FILES
  "*.js"
)
add_custom_target(hidden_files
  ALL
  SOURCES
    manifest.json.in
    js-scope.apparmor
    ${_JS_FILES}
)

# Add our main directories
add_subdirectory(data)
add_subdirectory(src)
