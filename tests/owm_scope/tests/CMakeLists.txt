# Where to find the scope ini file and .so
set(TEST_SCOPE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../scope")

file(GLOB_RECURSE
  TEST_FIXTURES
  "server/*.json"
  "*.py"
)

# Make this file show up in QtCreator
add_custom_target(hidden_test_fixtures ALL
  SOURCES ${TEST_FIXTURES}
)

# Where to find the test server binary
set(FAKE_SERVER "${CMAKE_CURRENT_SOURCE_DIR}/server/server.py")

# Add the unit tests
add_subdirectory(unit)
