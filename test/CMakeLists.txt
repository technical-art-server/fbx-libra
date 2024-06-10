cmake_minimum_required(VERSION 3.14)
project(TEST)

# ...
find_package(GTest REQUIRED)
# ...


enable_testing()

add_executable(
    ${PROJECT_NAME}
    gtest_sample.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    GTest::gtest_main
    gtest::gtest
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME} )