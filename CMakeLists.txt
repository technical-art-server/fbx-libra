cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)
project(All)

include(cmake/flatbuffer.cmake)

add_subdirectory(examples/EncodeSample)
add_subdirectory(examples/DecodeSample)
add_subdirectory(src/FbxLibra)
add_subdirectory(test)

add_dependencies(FbxLibra generate_flatbuffers_code)