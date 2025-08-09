include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(myvcs_tests test_repository.cpp)
target_link_libraries(myvcs_tests
  GTest::gtest_main
  myvcs_core
)

include(GoogleTest)
gtest_discover_tests(myvcs_tests)
