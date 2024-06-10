//
// Created by Tack2 on 2024/06/10.
//

#ifndef ALL_COUNTERWEIGHT_H
#define ALL_COUNTERWEIGHT_H

#include "ICounterWeightFbxConvertable.h"
#include "flatbuffers/flatbuffers.h"

class EmptyCounterWeight: public ICounterWeightFbxConvertable {
public:
    EmptyCounterWeight() = default;
    void Convert(flatbuffers::FlatBufferBuilder &builder, const std::string &fbx_path) override;
};

#endif //ALL_COUNTERWEIGHT_H
