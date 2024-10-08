﻿//
// Created by Tack2 on 2024/05/27.
//

#ifndef ALL_FBXLIBRA_H
#define ALL_FBXLIBRA_H

#include "Status.h"
#include "CounterWeight/HierarchyCounterWeight.h"

#include <memory>


class FBXLibraClient {
public:
    /// <summary>
    /// チェックする
    /// </summary>
    static Status Weigh(CounterWeight* weight, const CounterWeight* fbx_weight);
};



#endif //ALL_FBXLIBRA_H
