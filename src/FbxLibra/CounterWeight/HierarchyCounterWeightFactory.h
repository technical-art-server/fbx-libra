﻿//
// Created by Tack2 on 2024/06/13.
//

#ifndef ALL_HIERARCHYCOUNTERWEIGHTFACTORY_H
#define ALL_HIERARCHYCOUNTERWEIGHTFACTORY_H


#include <fbxsdk.h>
#include "CounterWeightFactory.h"
#include "cw_generated.h"

class HierarchyCounterWeightFactory: public CounterWeightFactory{
private:
    CounterWeight* CreateCounterWeight(const std::filesystem::path& fbx_path) override;
    CounterWeight* LoadCounterWeight(const std::filesystem::path& weight_path) override;
    flatbuffers::Offset<Weight::Node> CreateNode(FbxNode* pNode);
    void IncludeNode(std::vector<flatbuffers::Offset<Weight::Node>>& nodes, FbxNode* pNode, int depth = 0);
};


#endif //ALL_HIERARCHYCOUNTERWEIGHTFACTORY_H
