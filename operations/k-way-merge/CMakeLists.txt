add_executable(
  merge_test
  unit_tests/merge_test.cpp
)
target_link_libraries(
  merge_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(merge_test)
