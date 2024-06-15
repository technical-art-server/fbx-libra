cmake_minimum_required(VERSION 3.14)
project(TEST)

# ...
find_package(GTest REQUIRED)
find_package(flatbuffers)
find_package(magic_enum)
# ...


enable_testing()

# add_executable(
#     ${PROJECT_NAME}
#     gtest_sample.cpp
# )

# 再帰的にテストファイルを取得
set(SOURCE_FILES
        ../src/FbxLibra/Status.h
        ../src/FbxLibra/FlatBufferLoader.h
        ../src/FbxLibra/FBXLibra.h
        ../src/FbxLibra/FBXLibra.cpp
        ../src/FbxLibra/../../examples/data/hcw_generated.h
        ../src/FbxLibra/CounterWeight/HierarchyCounterWeight.h
        ../src/FbxLibra/CounterWeight/HierarchyCounterWeight.cpp
        ../src/FbxLibra/CounterWeight/CounterWeight.h
        ../src/FbxLibra/CounterWeight/CounterWeightFactory.h
        ../src/FbxLibra/CounterWeight/HierarchyCounterWeightFactory.h
        ../src/FbxLibra/CounterWeight/HierarchyCounterWeightFactory.cpp
        ../src/FbxLibra/CounterWeight/CounterWeightFactory.cpp
        ../src/FbxLibra/CounterWeight/CounterWeight.cpp
        gtest_sample.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# FBX SDKのインクルードディレクトリを指定
include_directories($ENV{FBX_SDK_PATH}/include)
include_directories(../src/FbxLibra)

target_link_libraries(
    ${PROJECT_NAME}
    GTest::gtest_main
    gtest::gtest
    flatbuffers::flatbuffers
    magic_enum::magic_enum
)
# FBX SDKライブラリとリンク
target_link_libraries(${PROJECT_NAME} libfbxsdk-md.lib libxml2-md.lib zlib-md.lib)

# target_link_libraries(${PROJECT_NAME} PRIVATE 
#FbxLibraのインクルードディレクトリを追加
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ../src/FbxLibra
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        DEBUG_POSTFIX "-d"
        RELEASE_POSTFIX "")

# FBX SDKライブラリのディレクトリ
target_link_directories(${PROJECT_NAME}
    PRIVATE
    $<$<CONFIG:Debug>:$ENV{FBX_SDK_PATH}/lib/x64/debug>
    $<$<CONFIG:Release>:$ENV{FBX_SDK_PATH}/lib/x64/release>
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})