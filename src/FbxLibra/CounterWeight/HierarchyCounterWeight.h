//
// Created by Tack2 on 2024/06/03.
//

#ifndef ALL_HIERARCHYCOUNTERWEIGHT_H
#define ALL_HIERARCHYCOUNTERWEIGHT_H

#include <fbxsdk.h>
#include "../../data/hcw_generated.h"
#include "ICounterWeightFbxConvertable.h"
#include "EmptyCounterWeight.h"

class HierarchyCounterWeight: public EmptyCounterWeight{

public:
    HierarchyCounterWeight() = default;
    explicit HierarchyCounterWeight(const char *file_path);

    bool operator==(const HierarchyCounterWeight&) const;

    void Convert(flatbuffers::FlatBufferBuilder& builder, const std::string& fbx_path) override;

private:
    static flatbuffers::Offset<FbxLibra::CounterWeight::Node> CreateNode(flatbuffers::FlatBufferBuilder& builder, FbxNode* pNode);
    void IncludeNode(flatbuffers::FlatBufferBuilder& builder, std::vector<flatbuffers::Offset<FbxLibra::CounterWeight::Node>>& nodes, FbxNode* pNode, int depth = 0);
    const FbxLibra::CounterWeight::Hierarchy* hierarchy{};
};

#endif //ALL_HIERARCHYCOUNTERWEIGHT_H
