cmake_minimum_required(VERSION 3.14)
project(TEST)

# ...
find_package(flatbuffers)
find_package(magic_enum)
# ...


# Flatcで生成されたファイルへの参照
include_directories(${GENERATED_DIR})

# プロジェクトのパスを取得
set(PROJECT_PATH ${CMAKE_SOURCE_DIR})

# 環境変数をC++コードに渡すためのヘッダーファイルを作成
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
    @ONLY
)

add_executable(${PROJECT_NAME}
    ../src/FbxLibra/Status.h
    ../src/FbxLibra/FlatBufferLoader.h
    ../src/FbxLibra/FBXLibra.h
    ../src/FbxLibra/FBXLibra.cpp
    ../src/FbxLibra/CounterWeight/HierarchyCounterWeight.h
    ../src/FbxLibra/CounterWeight/HierarchyCounterWeight.cpp
    ../src/FbxLibra/CounterWeight/CounterWeight.h
    ../src/FbxLibra/CounterWeight/CounterWeightFactory.h
    ../src/FbxLibra/CounterWeight/HierarchyCounterWeightFactory.h
    ../src/FbxLibra/CounterWeight/HierarchyCounterWeightFactory.cpp
    ../src/FbxLibra/CounterWeight/VertexCounterWeight.h
    ../src/FbxLibra/CounterWeight/VertexCounterWeight.cpp
    ../src/FbxLibra/CounterWeight/VertexCounterWeightFactory.h
    ../src/FbxLibra/CounterWeight/VertexCounterWeightFactory.cpp
    ../src/FbxLibra/CounterWeight/CounterWeightFactory.cpp
    ../src/FbxLibra/CounterWeight/CounterWeight.cpp
    gtest_sample.cpp
    gtest_create_hierarchy.cpp
    gtest_vertex.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    GTest::gtest_main
    gtest::gtest
    flatbuffers::flatbuffers
    magic_enum::magic_enum
)

# FBX SDKの設定
target_include_directories(${PROJECT_NAME} PRIVATE $ENV{FBX_SDK_PATH}/include)
target_link_directories(${PROJECT_NAME}
        PRIVATE
        $<$<CONFIG:Debug>:$ENV{FBX_SDK_PATH}/lib/x64/debug>
        $<$<CONFIG:Release>:$ENV{FBX_SDK_PATH}/lib/x64/release>
)
target_link_libraries(${PROJECT_NAME} libfbxsdk-md.lib libxml2-md.lib zlib-md.lib)

#FbxLibraのインクルードディレクトリを追加
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ../src/FbxLibra
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        DEBUG_POSTFIX "-d"
        RELEASE_POSTFIX "")

# CTestにテストプロジェクトを追加
gtest_discover_tests(${PROJECT_NAME})