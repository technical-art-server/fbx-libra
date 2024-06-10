//
// Created by Tack2 on 2024/06/03.
//

#ifndef ALL_FLATBUFFERLOADERR_H
#define ALL_FLATBUFFERLOADERR_H

#include <fstream>

class FlatBufferLoader {
public:
    template<typename T>
    static T* Load(const char *file_path, T* (func)(const void*));
};


template<typename T> T* FlatBufferLoader::Load(const char *file_path, T* (func)(const void *)) {
    std::ifstream fin(file_path, std::ios::in | std::ios::binary);
    if (!fin) {
        return nullptr;
    }

    auto begin = fin.tellg();
    fin.seekg(0, std::ifstream::end);
    auto end = fin.tellg();
    fin.clear();
    fin.seekg(0, std::ifstream::beg);
    auto len = end - begin;
    auto buf = new char[len + 1];
    fin.read(buf, len);
    fin.close();

    return func((uint8_t*)buf);
}

#endif //ALL_FLATBUFFERLOADERR_H
