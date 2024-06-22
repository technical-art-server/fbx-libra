//
// Created by Tack2 on 2024/06/13.
//

#include <fstream>
#include <iostream>
#include <filesystem>
#include "CounterWeight.h"
#include "../Status.h"

bool CounterWeight::Equal(const CounterWeight &other) {
    return EqualCounterWeight(other);
}

Status CounterWeight::Save(flatbuffers::FlatBufferBuilder &builder, const std::filesystem::path& path) {
    uint8_t * buf = builder.GetBufferPointer();
    size_t size = builder.GetSize();
    std::ofstream stream;
    auto abs_path = std::filesystem::absolute(path);
    if (!std::filesystem::exists(abs_path.parent_path())){
        std::filesystem::create_directory(abs_path.parent_path());
    }
    stream.open(path.string(), std::ios::out | std::ios::binary | std::ios::trunc);
    if (!stream){
        std::cerr << "Failed to open file." << std::endl;
        return Status::FAILURE;
    }

    stream.write((char*)buf, (std::streamsize)size);
    stream.close();
    return Status::SUCCESS;
}
