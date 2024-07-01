#ifndef ALL_VERTEXCOUNTERWEIGHTFACTORY_H
#define ALL_VERTEXCOUNTERWEIGHTFACTORY_H


#include <fbxsdk.h>
#include "CounterWeightFactory.h"
#include "cw_generated.h"

class VertexCounterWeightFactory : public CounterWeightFactory {
private:
    CounterWeight* CreateCounterWeight(const std::filesystem::path& fbx_path) override;
    CounterWeight* LoadCounterWeight(const std::filesystem::path& weight_path) override;

    // 再帰的にシーンを処理してメッシュノードを取得する
    void IncludeMeshNodes(FbxNode* node, std::vector<FbxNode*>& meshNodes);
};

#endif //ALL_VERTEXCOUNTERWEIGHTFACTORY_H