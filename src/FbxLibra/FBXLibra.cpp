//
// Created by Tack2 on 2024/05/27.
//

#include "FBXLibra.h"

Status FBXLibraClient::Weigh(CounterWeight* weight, CounterWeight* fbx_weight) {
    Status result;
    if (weight->Equal(*fbx_weight)){
        result = Status::SUCCESS;
    } else{
        result = Status::FAILURE;
    }

    return result;
}