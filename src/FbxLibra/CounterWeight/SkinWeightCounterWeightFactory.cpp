//
// Created by Tack2 on 2024/07/17.
//

#include "SkinWeightCounterWeightFactory.h"

#include <iostream>

#include "../FlatBufferLoader.h"
#include "cw_generated.h"
#include "SkinWeightCounterWeight.h"

CounterWeight *SkinWeightCounterWeightFactory::CreateCounterWeight(const std::filesystem::path &fbx_path) {
    FbxManager* manager = FbxManager::Create();
    FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT);
    manager->SetIOSettings(ios);

    FbxImporter* importer = FbxImporter::Create(manager, "");
    if (!importer->Initialize(fbx_path.string().c_str(), -1, manager->GetIOSettings())) {
        std::cerr << "Failed to initialize FBX importer: " << importer->GetStatus().GetErrorString() << std::endl;
        return nullptr;
    }
    FbxScene* scene = FbxScene::Create(manager, "Scene");
    importer->Import(scene);

    std::vector<flatbuffers::Offset<Weight::SkinWeight>> skinWeightList;
    FbxNode* rootNode = scene->GetRootNode();
    if (rootNode)
    {
        ProcessNode(rootNode, skinWeightList);
    }

    auto skin_weights_offset = builder->CreateVector(skinWeightList);
    auto skin_weights = CreateSkinWeights(*builder, skin_weights_offset);
    builder->Finish(skin_weights);

    auto skinWeights = flatbuffers::GetRoot<Weight::SkinWeights>(builder->GetBufferPointer());
    return new SkinWeightCounterWeight(skinWeights);
}

CounterWeight* SkinWeightCounterWeightFactory::LoadCounterWeight(const std::filesystem::path &weight_path) {
    auto weight = FlatBufferLoader::Load<Weight::SkinWeights>(weight_path.string().c_str());
    return new SkinWeightCounterWeight(weight);
}

void SkinWeightCounterWeightFactory::ProcessNode(FbxNode* node, const std::vector<flatbuffers::Offset<Weight::SkinWeight>>& skinWeights)
{
    if (!node) return;

    FbxNodeAttribute* attribute = node->GetNodeAttribute();
    if (attribute && attribute->GetAttributeType() == FbxNodeAttribute::eMesh) {
        auto mesh = static_cast<FbxMesh*>(attribute);
        WriteSkinWeights(mesh, skinWeights);
    }

    int childCount = node->GetChildCount();
    for (int i = 0; i < childCount; ++i) {
        std::cout << i << node->GetChild(i)->GetName() << std::endl;
        ProcessNode(node->GetChild(i), skinWeights);
    }
}

void SkinWeightCounterWeightFactory::WriteSkinWeights(const FbxMesh* mesh, std::vector<flatbuffers::Offset<Weight::SkinWeight>> skinWeights)
{
    if (!mesh) return;

    const int skin_count = mesh->GetDeformerCount(FbxDeformer::eSkin);
    for (int i = 0; i < skin_count; ++i) {
        auto* fbx_skin = static_cast<FbxSkin*>(mesh->GetDeformer(i, FbxDeformer::eSkin));
        if (!fbx_skin) continue;

        const int cluster_count = fbx_skin->GetClusterCount();
        for (int j = 0; j < cluster_count; ++j) {
            FbxCluster* cluster = fbx_skin->GetCluster(j);
            if (!cluster) continue;

            const int numIndices = cluster->GetControlPointIndicesCount();
            const int* indices = cluster->GetControlPointIndices();
            const double* weights = cluster->GetControlPointWeights();

            std::vector<flatbuffers::Offset<Weight::Skin>> skines;
            std::vector<flatbuffers::Offset<Weight::SkinCluster>> clusters;
            for (int k = 0; k < numIndices; ++k) {
                auto skin = Weight::CreateSkin(*builder, indices[k], weights[k]);
                skines.push_back(skin);
            }
            auto skinCluster = Weight::CreateSkinCluster(*builder, builder->CreateVector(skines));
            clusters.push_back(skinCluster);

            flatbuffers::Offset<::flatbuffers::String> mesh_name = builder->CreateString(mesh->GetName());
            auto skinWeight = CreateSkinWeight(*builder, mesh_name, builder->CreateVector(clusters));
            skinWeights.push_back(skinWeight);
        }
    }
}
