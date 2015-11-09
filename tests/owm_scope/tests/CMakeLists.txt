file(GLOB_RECURSE
  TEST_FIXTURES
  "server/*.json"
  "*.py"
)

# Make these files show up in QtCreator
add_custom_target(hidden_test_fixtures ALL
  SOURCES ${TEST_FIXTURES}
)

# Where to find the scope ini file
set(TEST_SCOPE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../scope")

# Where to find the test server binary
set(FAKE_SERVER "${CMAKE_CURRENT_SOURCE_DIR}/server/server.py")

# Register the test with CTest
add_test(
  owm_scope-tests
  "${CMAKE_CURRENT_SOURCE_DIR}/test-scope.py" "owm_scope" "${TEST_SCOPE_DIRECTORY}/owm_scope.ini" "${FAKE_SERVER}"
)
