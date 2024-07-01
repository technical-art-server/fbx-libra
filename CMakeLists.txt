cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)
project(All)

include(cmake/fbxsdk.cmake)
include(cmake/flatbuffer.cmake)

add_subdirectory(examples/EncodeSample)
add_subdirectory(examples/DecodeSample)
add_subdirectory(src/FbxLibra)
add_dependencies(FbxLibra generate_flatbuffers_code)


# Test用の設定
enable_testing()
include(cmake/gtest.cmake)
add_subdirectory(test)
add_dependencies(TEST generate_flatbuffers_code)
