//
// Created by Tack2 on 2024/06/03.
//

#ifndef ALL_ICOUNTERWEIGHTFBXCONVERTABLE_H
#define ALL_ICOUNTERWEIGHTFBXCONVERTABLE_H

#include <string>
#include <flatbuffers/flatbuffers.h>

class ICounterWeightFbxConvertable {
public:
    virtual void Convert(flatbuffers::FlatBufferBuilder& builder, const std::string& fbx_path) = 0;
};

#endif //ALL_ICOUNTERWEIGHTFBXCONVERTABLE_H
