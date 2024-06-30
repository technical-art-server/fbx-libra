# CMakeの引数指定でFBX SDKのパスを受け取る
option(FBX_SDK_ROOT "Path to root of fbx-sdk" OFF)

if (FBX_SDK_ROOT)
    message(STATUS "FBX SDK found at CMake ${FBX_SDK_ROOT}")
endif()

# 環境変数に入ってるかチェック
if (NOT EXISTS ${FBX_SDK_ROOT})
    message(STATUS "FBX SDK found at ENV ${FBX_SDK_ROOT}")
    set(FBX_SDK_ROOT $ENV{FBX_SDK_PATH} PATH "Path to root of fbx-sdk")
endif()

# 環境変数に入ってない場合はデフォルトのパスを設定
if (NOT EXISTS ${FBX_SDK_ROOT})
    if(NOT DEFINED FBX_SDK_VERSION)
        set(FBX_SDK_VERSION 2020.3.7 STRING "fbx sdk version")
    endif()

    if(WIN32)
        # Windows
        set(AUDODESK_INSTALL_BASE_DEFAULT "C:/Program Files/Autodesk")
    elseif(APPLE)
        # Apple
        set(AUDODESK_INSTALL_BASE_DEFAULT /Applications/Autodesk)
    else()
        # Linux
        set(AUDODESK_INSTALL_BASE_DEFAULT /usr/autodesk)
    endif()

    set(AUDODESK_INSTALL_BASE_PATH ${AUDODESK_INSTALL_BASE_DEFAULT} STRING
    "Root path containing your maya installations, e.g. /usr/autodesk or /Applications/Autodesk/")

    set(FBX_SDK_ROOT ${AUDODESK_INSTALL_BASE_DEFAULT}/FBX/FBX\ SDK/${FBX_SDK_VERSION})
    message(STATUS "FBX SDK found at DEFAULT ${FBX_SDK_ROOT}")
endif()

# パスが存在しない場合はエラー
if (NOT EXISTS ${FBX_SDK_ROOT})
    message(FATAL_ERROR "FBX SDK not found at ${FBX_SDK_ROOT}")
else()
    set(FBX_SDK_INCLUDE_DIR ${FBX_SDK_ROOT}/include)
    set(FBX_SDK_LIB_DIR ${FBX_SDK_ROOT}/lib/x64)
    if (NOT EXISTS ${FBX_SDK_LIB_DIR})
        set(FBX_SDK_LIB_DIR ${FBX_SDK_ROOT}/lib/vs2015/x64)
    endif()
    set(FBX_SDK_FOUND TRUE)
endif()