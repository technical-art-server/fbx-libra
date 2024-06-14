//
// Created by Tack2 on 2024/06/13.
//

#include "CounterWeightFactory.h"

CounterWeight *CounterWeightFactory::Create(const std::string &fbx_path) {
    return CreateCounterWeight(fbx_path);
}

CounterWeight *CounterWeightFactory::Load(const std::string &weight_path) {
    return LoadCounterWeight(weight_path);
}

CounterWeightFactory::CounterWeightFactory() {
    auto* newBuilder = new flatbuffers::FlatBufferBuilder(2048);
    this->builder = newBuilder;
}

CounterWeightFactory::~CounterWeightFactory() {
    this->builder->Clear();
    delete this->builder;
}
