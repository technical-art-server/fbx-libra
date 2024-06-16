cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)
project(All)
add_subdirectory(examples/EncodeSample)
add_subdirectory(examples/DecodeSample)
add_subdirectory(src/FbxLibra)

# Test用の設定
enable_testing()
include(cmake/gtest.cmake)
add_subdirectory(test)