//
// Created by Tack2 on 2024/05/27.
//

#ifndef ALL_FBXLIBRA_H
#define ALL_FBXLIBRA_H

#include "../../examples/data/hcw_generated.h"
#include "CounterWeight/ICounterWeightFbxConvertable.h"
#include "Status.h"
#include "CounterWeight/HierarchyCounterWeight.h"

#include <memory>


class FBXLibraClient {
public:
    /// <summary>
    /// チェックする
    /// </summary>
    template <typename T, typename U>
    Status Weigh(T* weight, T* fbx_weight);
};

template <typename T, typename U>
Status FBXLibraClient::Weigh(T* weight, T* fbx_weight) {
//    T fbx_weight{};
//    flatbuffers::FlatBufferBuilder builder(1024);
//    fbx_weight.Convert(builder, fbx_path);

    Status result;
    if (*(U*)weight == *(U*)fbx_weight){
        result = Status::SUCCESS;
    } else{
        result = Status::FAILURE;
    }

//    builder.Clear();
//    delete fbx_weight;
    return result;
}

#endif //ALL_FBXLIBRA_H
