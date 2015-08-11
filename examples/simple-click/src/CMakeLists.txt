# Unpack node_modules.tgz
message(STATUS "Unpacking node modules")

execute_process(
  COMMAND tar xf node_modules.tgz
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  RESULT_VARIABLE _UNPACK_RESULT
)

if(NOT _UNPACK_RESULT EQUAL 0)
  message(FATAL_ERROR "Failed to unpack node modules")
endif()

# Put the logo, ini, and js files in the build directory next
# to the scope .so file so test tools can find them easily.
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/../data/logo.png"
  "${CMAKE_CURRENT_BINARY_DIR}/logo.png"
  @ONLY
  COPYONLY
)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/../data/${SCOPE_NAME}.ini.in"
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

file(
  COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/node_modules"
  DESTINATION
    ${CMAKE_CURRENT_BINARY_DIR}
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
)
