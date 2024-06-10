cmake_minimum_required(VERSION 3.14)
project(EncodeSample)

include_directories($ENV{FBX_SDK_PATH}/include)

find_package(flatbuffers)

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

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ignore:4099")

# FBX SDKライブラリとリンク
target_link_libraries(${PROJECT_NAME} libfbxsdk-md.lib libxml2-md.lib zlib-md.lib)

target_link_libraries(${PROJECT_NAME}
        flatbuffers::flatbuffers
)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} //MDd" CACHE STRING "description")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD" CACHE STRING "description")


# C++の標準規格の指定
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/examples/data/fbx/dragon.fbx $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

#add_dependencies(${PROJECT_NAME} TARGET)