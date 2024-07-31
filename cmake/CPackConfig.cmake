# installer rules.
set(CPACK_PACKAGE_NAME "FbxLibra")
set(CPACK_PACKAGE_VENDOR "technical artist server")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Tools to compare fbx files.")

# パッケージ形式の指定 (ZIP)
set(CPACK_GENERATOR "ZIP")

# インストールディレクトリの設定
include(CPack)