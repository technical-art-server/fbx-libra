# fbx-Libra
Tools to compare fbx files.  
The name of the tool was inspired by the word "compare," and was named after the constellation Libra.

# dependency environment
- Windows
  - Cmake is not able to support non-Windows.
- Cmake 3.14 or higher


# Building
## 1. Conanをインストールする
素のC+++を利用するのは大変なので、Conanを利用する。  
色々なインストール方法があるが、pythonをオススメし、 以降の実行は全てこのPythonの環境下での実行を想定する。  
```bash
python -m venv .venv
".venv\Scripts\activate.bat"
pip install conan
```

## 2. FBX_SDKのパスを環境変数に指定
``` bash
set FBX_SDK_PATH=C:\Program Files\Autodesk\FBX\FBX SDK\2020.3.7
```

## 3. cmakeで環境構築する
``` bash
cmake -B build -S . -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=conan_provider.cmake -DCMAKE_BUILD_TYPE=Debug

# FBX_SDK_ROOTにFBX SDKのパスをCMakeの変数に指定も可
cmake -B build -S . \
  -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=conan_provider.cmake \
  -DFBX_SDK_ROOT="C:\Program Files\Autodesk\FBX\FBX SDK\2020.3.7" \
  -DCMAKE_BUILD_TYPE=Debug

```
## 2. ビルドする
下記コマンドを実行し、ビルド成功すると環境構築は完了している状態。　　
``` bash
cmake --build build --config Debug
```

# Related Documents
- [DesignDoc](doc/DesignDoc.md)
- [メモ](doc/メモ.md)