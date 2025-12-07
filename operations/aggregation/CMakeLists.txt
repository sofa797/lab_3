add_executable(
  aggregation_test
  unit_tests/aggregation_test.cpp
)
target_link_libraries(
  aggregation_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(aggregation_test)
