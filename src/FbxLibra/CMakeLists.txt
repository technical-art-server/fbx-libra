cmake_minimum_required(VERSION 3.14)
project(FbxLibra)

find_package(args-parser)
find_package(flatbuffers)

# FBX SDKのインクルードディレクトリを指定
include_directories($ENV{FBX_SDK_PATH}/include)

# ソースファイルの設定
set(SOURCE_FILES
        main.cpp
        ../data/hcw_generated.h
)

# 実行ファイルを生成
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
        DEBUG_POSTFIX "-d"
        RELEASE_POSTFIX "")

# FBX SDKライブラリのディレクトリ
target_link_directories(${PROJECT_NAME}
        PRIVATE
        $<$<CONFIG:Debug>:$ENV{FBX_SDK_PATH}/lib/x64/debug>
        $<$<CONFIG:Release>:$ENV{FBX_SDK_PATH}/lib/x64/release>
)

target_link_libraries(${PROJECT_NAME}
        args-parser::args-parser
        flatbuffers::flatbuffers
)


set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ignore:4099")

# FBX SDKライブラリとリンク
target_link_libraries(${PROJECT_NAME} libfbxsdk-md.lib libxml2-md.lib zlib-md.lib)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} //MDd" CACHE STRING "description")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD" CACHE STRING "description")

# C++の標準規格の指定
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
