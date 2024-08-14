cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

project(FbxLibra)

find_package(args-parser)
find_package(flatbuffers)
find_package(magic_enum)


# FBX SDKのインクルードディレクトリを指定
include_directories(${FBX_SDK_INCLUDE_DIR})
# Flatcで生成されたファイルのディレクトリを指定
include_directories(${GENERATED_DIR})

# ソースファイルの設定
set(SOURCE_FILES
        main.cpp
        Status.h
        FlatBufferLoader.h
        FBXLibra.h
        FBXLibra.cpp
        CounterWeight/HierarchyCounterWeight.h
        CounterWeight/HierarchyCounterWeight.cpp
        CounterWeight/CounterWeight.h
        CounterWeight/CounterWeightFactory.h
        CounterWeight/HierarchyCounterWeightFactory.h
        CounterWeight/HierarchyCounterWeightFactory.cpp
        CounterWeight/CounterWeightFactory.cpp
        CounterWeight/CounterWeight.cpp
        CounterWeight/VertexCounterWeight.h
        CounterWeight/VertexCounterWeight.cpp
        CounterWeight/VertexCounterWeightFactory.h
        CounterWeight/VertexCounterWeightFactory.cpp
        CounterWeight/SkinWeightCounterWeight.h
        CounterWeight/SkinWeightCounterWeight.cpp
        CounterWeight/SkinWeightCounterWeightFactory.h
        CounterWeight/SkinWeightCounterWeightFactory.cpp
)

# 実行ファイルを生成
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
        DEBUG_POSTFIX "-d"
        RELEASE_POSTFIX "")

# FBX SDKライブラリのディレクトリ
target_link_directories(${PROJECT_NAME}
        PRIVATE
        $<$<CONFIG:Debug>:${FBX_SDK_LIB_DIR}/debug>
        $<$<CONFIG:Release>:${FBX_SDK_LIB_DIR}/release>
)

target_link_libraries(${PROJECT_NAME}
        args-parser::args-parser
        flatbuffers::flatbuffers
        magic_enum::magic_enum
)


set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ignore:4099")

# FBX SDKライブラリとリンク
target_link_libraries(${PROJECT_NAME} ${FBX_SDK_LIBS})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} //MDd" CACHE STRING "description")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD" CACHE STRING "description")

# C++の標準規格の指定
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
