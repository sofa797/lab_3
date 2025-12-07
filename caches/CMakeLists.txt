add_executable(
  cache_test
  unit_tests/cache_test.cpp
)
target_link_libraries(
  cache_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(cache_test)
