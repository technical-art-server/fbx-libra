//
// Created by Tack2 on 2024/06/13.
//

#include <iostream>
#include "HierarchyCounterWeightFactory.h"
#include "HierarchyCounterWeight.h"
#include "../FlatBufferLoader.h"
#include "flatbuffers/flatbuffers.h"

CounterWeight *HierarchyCounterWeightFactory::CreateCounterWeight(const std::filesystem::path &fbx_path) {
    FbxManager* manager = FbxManager::Create();
    FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT);
    manager->SetIOSettings(ios);

    FbxImporter* importer = FbxImporter::Create(manager, "");

    if (!importer->Initialize(fbx_path.string().c_str(), -1, manager->GetIOSettings())){
        std::cerr << "Failed to initialize FBX importer: " << importer->GetStatus().GetErrorString() << std::endl;
        return nullptr;
    }

    FbxScene* scene = FbxScene::Create(manager, "Scene");
    importer->Import(scene);

    FbxNode* rootNode = scene->GetRootNode();

    std::vector<flatbuffers::Offset<Weight::Node>> nodes;
    if (rootNode){
        for (int i =0; i < rootNode->GetChildCount(); i++){
            IncludeNode(nodes, rootNode->GetChild(i));
        }
    }

    auto f_nodes = builder->CreateVector(nodes);
    auto hierarchy_offset = Weight::CreateHierarchy(*this->builder, f_nodes);
    this->builder->Finish(hierarchy_offset);
    auto new_hierarchy = flatbuffers::GetRoot<Weight::Hierarchy>(builder->GetBufferPointer());

    importer->Destroy();
    scene->Destroy();
    ios->Destroy();
    manager->Destroy();

    return new HierarchyCounterWeight(new_hierarchy);
}

void HierarchyCounterWeightFactory::IncludeNode(std::vector<flatbuffers::Offset<Weight::Node>> &nodes, FbxNode *pNode, int depth) {
    if (!pNode) return;

    auto node = CreateNode(pNode);
    nodes.push_back(node);

    // 子ノードを再帰的に処理
    int childCount = pNode->GetChildCount();
    for (int i = 0; i < childCount; i++) {
        IncludeNode(nodes, pNode->GetChild(i), depth + 1);
    }
}

flatbuffers::Offset<Weight::Node>
HierarchyCounterWeightFactory::CreateNode(FbxNode *pNode) {
    auto node_name = this->builder->CreateString(pNode->GetName());

    FbxDouble3 fbx_trans = pNode->LclTranslation.Get();
    FbxDouble3 fbx_rot = pNode->LclRotation.Get();
    FbxDouble3 scaling = pNode->LclScaling.Get();

    Weight::Vector3 position = Weight::Vector3(fbx_trans[0], fbx_trans[1], fbx_trans[2]);
    Weight::Vector3 rotation = Weight::Vector3(fbx_rot[0], fbx_rot[1], fbx_rot[2]);
    Weight::Vector3 scale = Weight::Vector3(scaling[0], scaling[1], scaling[2]);

    auto transform = CreateTransform(*this->builder, &position, &rotation, &scale);
    auto node = Weight::CreateNode(*this->builder, node_name, transform);

    return node;
}

CounterWeight *HierarchyCounterWeightFactory::LoadCounterWeight(const std::filesystem::path &weight_path) {
    auto weight = FlatBufferLoader::Load<Weight::Hierarchy>(weight_path.string().c_str());
    return new HierarchyCounterWeight(weight);
}
