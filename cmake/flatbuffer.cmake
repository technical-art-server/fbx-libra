find_package(flatbuffers)

# スキーマファイルのパスを複数指定
set(SCHEMA_FILES
    "${CMAKE_SOURCE_DIR}/src/FbxLibra/data/cw.fbs"
)

# 生成されるソースファイルの出力ディレクトリを指定
set(GENERATED_DIR "${CMAKE_BINARY_DIR}/generated")

# 生成されるヘッダーファイルとソースファイルをリスト
set(GENERATED_FILES)

# スキーマファイルから生成されるファイルをリストに追加
foreach(SCHEMA_FILE ${SCHEMA_FILES})
    get_filename_component(SCHEMA_NAME ${SCHEMA_FILE} NAME_WE)
    list(APPEND GENERATED_FILES "${GENERATED_DIR}/${SCHEMA_NAME}_generated.h")
endforeach()

# スキーマファイルからコードを生成するカスタムコマンドを追加
add_custom_command(
    OUTPUT ${GENERATED_FILES}
    COMMAND ${FLATBUFFERS_FLATC_EXECUTABLE} --cpp -o ${GENERATED_DIR} ${SCHEMA_FILES}
    DEPENDS ${SCHEMA_FILES}
    COMMENT "Running flatc compiler on ${SCHEMA_FILE}"
)

# カスタムターゲットを追加
add_custom_target(generate_flatbuffers_code ALL DEPENDS ${GENERATED_FILES})