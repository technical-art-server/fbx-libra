//
// Created by Tack2 on 2024/06/03.
//
#include <iostream>
#include "HierarchyCounterWeight.h"
#include <fbxsdk.h>
#include <fstream>
#include "../FlatBufferLoader.h"


void HierarchyCounterWeight::Convert(flatbuffers::FlatBufferBuilder& builder, const std::string& fbx_path) {
    FbxManager* manager = FbxManager::Create();
    FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT);
    manager->SetIOSettings(ios);

    FbxImporter* importer = FbxImporter::Create(manager, "");

    if (!importer->Initialize(fbx_path.c_str(), -1, manager->GetIOSettings())){
        std::cerr << "Failed to initialize FBX importer: " << importer->GetStatus().GetErrorString() << std::endl;
        return;
    }

    FbxScene* scene = FbxScene::Create(manager, "Scene");
    importer->Import(scene);
    importer->Destroy();

    FbxNode* rootNode = scene->GetRootNode();

    std::vector<flatbuffers::Offset<FbxLibra::CounterWeight::Node>> nodes;
    if (rootNode){
        for (int i =0; i < rootNode->GetChildCount(); i++){
            IncludeNode(builder, nodes, rootNode->GetChild(i));
        }
    }
    manager->Destroy();

    auto f_nodes = builder.CreateVector(nodes);
    auto hierarchy_offset = CreateHierarchy(builder, f_nodes);
    FinishHierarchyBuffer(builder, hierarchy_offset);

    auto new_hierarchy = FbxLibra::CounterWeight::GetHierarchy(builder.GetBufferPointer());
    hierarchy = new_hierarchy;
}

void HierarchyCounterWeight::IncludeNode(flatbuffers::FlatBufferBuilder &builder,
                                         std::vector<flatbuffers::Offset<FbxLibra::CounterWeight::Node>> &nodes,
                                         FbxNode *pNode, int depth) {
    if (!pNode) return;

    auto node = CreateNode(builder, pNode);
    nodes.push_back(node);

    // 子ノードを再帰的に処理
    int childCount = pNode->GetChildCount();
    for (int i = 0; i < childCount; i++) {
        IncludeNode(builder, nodes, pNode->GetChild(i), depth + 1);
    }
}

flatbuffers::Offset<FbxLibra::CounterWeight::Node>
HierarchyCounterWeight::CreateNode(flatbuffers::FlatBufferBuilder &builder, FbxNode *pNode) {
    auto node_name = builder.CreateString(pNode->GetName());

    FbxDouble3 fbx_trans = pNode->LclTranslation.Get();
    FbxDouble3 fbx_rot = pNode->LclRotation.Get();
    FbxDouble3 scaling = pNode->LclScaling.Get();

    FbxLibra::CounterWeight::Vector3 position = FbxLibra::CounterWeight::Vector3(fbx_trans[0], fbx_trans[1], fbx_trans[2]);
    FbxLibra::CounterWeight::Vector3 rotation = FbxLibra::CounterWeight::Vector3(fbx_rot[0], fbx_rot[1], fbx_rot[2]);
    FbxLibra::CounterWeight::Vector3 scale = FbxLibra::CounterWeight::Vector3(scaling[0], scaling[1], scaling[2]);

    auto transform = CreateTransform(builder, &position, &rotation, &scale);
    auto node = FbxLibra::CounterWeight::CreateNode(builder, node_name, transform);

    return node;
}

// コンストラクター
HierarchyCounterWeight::HierarchyCounterWeight(const char *file_path) {
    hierarchy = FlatBufferLoader::Load(file_path, FbxLibra::CounterWeight::GetHierarchy);
}

// 等価演算子オーバーロード
// 中身のアイテムが一緒なら同様とみなす
bool HierarchyCounterWeight::operator==(const HierarchyCounterWeight &other) const {
    if (hierarchy == nullptr || other.hierarchy == nullptr) return false;
    auto nodes = hierarchy->nodes();
    auto otherNodes = other.hierarchy->nodes();

    if (nodes->size() != otherNodes->size()) {
        return false;
    }

    for (int i = 0; i < nodes->size(); i++) {
        auto dest_node = nodes->Get(i);
        auto src_node = otherNodes->Get(i);
        if (dest_node->name()->str() != src_node->name()->str()) {
            return false;
        }
        auto dest_transform = dest_node->transform();
        auto src_transform = src_node->transform();
        if (dest_transform->position()->x() != src_transform->position()->x() ||
            dest_transform->position()->y() != src_transform->position()->y() ||
            dest_transform->position()->z() != src_transform->position()->z()) {
            return false;
        }
        if (dest_transform->rotation()->x() != src_transform->rotation()->x() ||
            dest_transform->rotation()->y() != src_transform->rotation()->y() ||
            dest_transform->rotation()->z() != src_transform->rotation()->z()) {
            return false;
        }
        if (dest_transform->scale()->x() != src_transform->scale()->x() ||
            dest_transform->scale()->y() != src_transform->scale()->y() ||
            dest_transform->scale()->z() != src_transform->scale()->z()) {
            return false;
        }
    }

    return true;
}




