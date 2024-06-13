//
// Created by Tack2 on 2024/06/13.
//

#include <iostream>
#include "HierarchyCounterWeightFactory.h"
#include "HierarchyCounterWeight.h"
#include "../FlatBufferLoader.h"

CounterWeight *HierarchyCounterWeightFactory::CreateCounterWeight(const std::string &fbx_path) {
    FbxManager* manager = FbxManager::Create();
    FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT);
    manager->SetIOSettings(ios);

    FbxImporter* importer = FbxImporter::Create(manager, "");

    if (!importer->Initialize(fbx_path.c_str(), -1, manager->GetIOSettings())){
        std::cerr << "Failed to initialize FBX importer: " << importer->GetStatus().GetErrorString() << std::endl;
        return nullptr;
    }

    FbxScene* scene = FbxScene::Create(manager, "Scene");
    importer->Import(scene);
    importer->Destroy();

    FbxNode* rootNode = scene->GetRootNode();

    std::vector<flatbuffers::Offset<FbxLibra::CounterWeight::Node>> nodes;
    if (rootNode){
        for (int i =0; i < rootNode->GetChildCount(); i++){
            IncludeNode(nodes, rootNode->GetChild(i));
        }
    }
    manager->Destroy();

    auto f_nodes = builder->CreateVector(nodes);
    auto hierarchy_offset = FbxLibra::CounterWeight::CreateHierarchy(*this->builder, f_nodes);
    FinishHierarchyBuffer(*builder, hierarchy_offset);

    auto new_hierarchy = FbxLibra::CounterWeight::GetHierarchy(builder->GetBufferPointer());
    return new HierarchyCounterWeight(new_hierarchy);
}

void HierarchyCounterWeightFactory::IncludeNode(std::vector<flatbuffers::Offset<FbxLibra::CounterWeight::Node>> &nodes, FbxNode *pNode, int depth) {
    if (!pNode) return;

    auto node = CreateNode(pNode);
    nodes.push_back(node);

    // 子ノードを再帰的に処理
    int childCount = pNode->GetChildCount();
    for (int i = 0; i < childCount; i++) {
        IncludeNode(nodes, pNode->GetChild(i), depth + 1);
    }
}

flatbuffers::Offset<FbxLibra::CounterWeight::Node>
HierarchyCounterWeightFactory::CreateNode(FbxNode *pNode) {
    auto node_name = this->builder->CreateString(pNode->GetName());

    FbxDouble3 fbx_trans = pNode->LclTranslation.Get();
    FbxDouble3 fbx_rot = pNode->LclRotation.Get();
    FbxDouble3 scaling = pNode->LclScaling.Get();

    FbxLibra::CounterWeight::Vector3 position = FbxLibra::CounterWeight::Vector3(fbx_trans[0], fbx_trans[1], fbx_trans[2]);
    FbxLibra::CounterWeight::Vector3 rotation = FbxLibra::CounterWeight::Vector3(fbx_rot[0], fbx_rot[1], fbx_rot[2]);
    FbxLibra::CounterWeight::Vector3 scale = FbxLibra::CounterWeight::Vector3(scaling[0], scaling[1], scaling[2]);

    auto transform = CreateTransform(*this->builder, &position, &rotation, &scale);
    auto node = FbxLibra::CounterWeight::CreateNode(*this->builder, node_name, transform);

    return node;
}

CounterWeight *HierarchyCounterWeightFactory::LoadCounterWeight(const std::string &weight_path) {
    auto weight = FlatBufferLoader::Load(weight_path.c_str(), FbxLibra::CounterWeight::GetHierarchy);
    return new HierarchyCounterWeight(weight);
}
