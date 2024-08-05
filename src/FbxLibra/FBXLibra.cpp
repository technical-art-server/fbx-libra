//
// Created by Tack2 on 2024/05/27.
//

#include "FBXLibra.h"

Status FBXLibraClient::Weigh(CounterWeight* weight, const CounterWeight* fbx_weight) {
    Status result;
    if (fbx_weight == nullptr) {
        throw std::invalid_argument("fbx not found.");
    }

    if (weight->Equal(*fbx_weight)){
        result = Status::SUCCESS;
    } else{
        result = Status::FAILURE;
    }

    return result;
}