# This command ensures that test-scope.py has execute permission
execute_process(COMMAND chmod +x "${CMAKE_CURRENT_SOURCE_DIR}/test-scope.py")

# Register the test with CTest
add_test(
  owm_scope-tests
  "${CMAKE_CURRENT_SOURCE_DIR}/test-scope.py" "owm_scope" "${TEST_SCOPE_DIRECTORY}/owm_scope.ini" "${FAKE_SERVER}"
)
