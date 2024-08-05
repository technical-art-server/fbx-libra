//
// Created by Tack2 on 2024/07/17.
//

#ifndef ALL_SKINWEIGHTFACTORY_H
#define ALL_SKINWEIGHTFACTORY_H

#include <fbxsdk.h>
#include "CounterWeightFactory.h"
#include "CounterWeight.h"
#include "SkinWeightCounterWeight.h"

class SkinWeightCounterWeightFactory : public CounterWeightFactory {
private:
    CounterWeight* CreateCounterWeight(const std::filesystem::path& fbx_path) override;
    CounterWeight* LoadCounterWeight(const std::filesystem::path& weight_path) override;

    void ProcessNode(FbxNode* node, const std::vector<flatbuffers::Offset<Weight::SkinWeight>>&);
    void WriteSkinWeights(const FbxMesh* mesh, std::vector<flatbuffers::Offset<Weight::SkinWeight>>);
};


#endif //ALL_SKINWEIGHTFACTORY_H
