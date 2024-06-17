find_package(flatbuffers)

# ConanでインストールされたFlatBuffersのインストールディレクトリを指定
set(FLATBUFFERS_INSTALL_DIR "path/to/flatbuffers")

# flatcの実行ファイルを指定
set(FLATC_EXECUTABLE "${FLATBUFFERS_INSTALL_DIR}/bin/flatc")

# スキーマファイルのパスを複数指定
set(SCHEMA_FILE "${CMAKE_SOURCE_DIR}/examples/data/hcw.fbs")

# 生成されるソースファイルの出力ディレクトリを指定
set(GENERATED_DIR "${CMAKE_BINARY_DIR}/generated")

# 生成されるヘッダーファイルとソースファイル
set(GENERATED_FILES
    "${GENERATED_DIR}/hcw_generated.h"
)

# スキーマファイルからコードを生成するカスタムコマンドを追加
add_custom_command(
    OUTPUT ${GENERATED_FILES}
    COMMAND ${FLATC_EXECUTABLE} --cpp -o ${GENERATED_DIR} ${SCHEMA_FILE}
    DEPENDS ${SCHEMA_FILE}
    COMMENT "Running flatc compiler on ${SCHEMA_FILE}"
)

# カスタムターゲットを追加
add_custom_target(generate_flatbuffers_code ALL DEPENDS ${GENERATED_FILES})