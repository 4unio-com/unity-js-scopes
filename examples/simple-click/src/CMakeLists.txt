# Put the logo, ini, and js files in the build directory next
# to the scope .so file so test tools can find them easily.
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/../data/logo.png"
  "${CMAKE_CURRENT_BINARY_DIR}/logo.png"
  @ONLY
  COPYONLY
)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/${SCOPE_NAME}.ini.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${SCOPE_NAME}.ini"
  @ONLY
  COPYONLY
)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/${SCOPE_NAME}.js"
  "${CMAKE_CURRENT_BINARY_DIR}/${SCOPE_NAME}.js"
  @ONLY
  COPYONLY
)

add_custom_target(
  copy_node_modules ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/node_modules"
    "${CMAKE_CURRENT_BINARY_DIR}/node_modules"
)

# Install the scope ini and js files
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${SCOPE_NAME}.ini"
    "${CMAKE_CURRENT_SOURCE_DIR}/${SCOPE_NAME}.js"
  DESTINATION
    ${SCOPE_INSTALL_DIR}
)

install(
  DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/node_modules"
  DESTINATION
    ${SCOPE_INSTALL_DIR}
  USE_SOURCE_PERMISSIONS
)
