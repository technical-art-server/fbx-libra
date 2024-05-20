#include <iostream>
#include <fstream>
#include <fbxsdk.h>
#include <filesystem>

#include "../data/hcw_generated.h"

using namespace std;
using namespace FbxLibra::CounterWeight;

flatbuffers::Offset<Node> CreateNode(flatbuffers::FlatBufferBuilder& builder, FbxNode* pNode){
    if (!pNode) return 0;

    auto node_name = builder.CreateString(pNode->GetName());

    FbxDouble3 fbx_trans = pNode->LclTranslation.Get();
    FbxDouble3 fbx_rot = pNode->LclRotation.Get();
    FbxDouble3 scaling = pNode->LclScaling.Get();

    Vector3 position = Vector3(fbx_trans[0], fbx_trans[1], fbx_trans[2]);
    Vector3 rotation = Vector3(fbx_rot[0], fbx_rot[1], fbx_rot[2]);
    Vector3 scale = Vector3(scaling[0], scaling[1], scaling[2]);

    auto transform = CreateTransform(builder, &position, &rotation, &scale);

    auto node = CreateNode(builder, node_name, transform);

    return node;
}


void IncludeNode(flatbuffers::FlatBufferBuilder& builder, std::vector<flatbuffers::Offset<Node>>& nodes, FbxNode* pNode, int depth = 0) {
    if (!pNode) return;

    // インデントを出力して階層を表示
    for (int i = 0; i < depth; i++) std::cout << "  ";

    // ノード名を出力
    std::cout << pNode->GetName() << std::endl;

    // トランスフォームの値を取得して出力
    FbxDouble3 translation = pNode->LclTranslation.Get();
    double trans_d[3] = {translation[0], translation[1], translation[2]};

    FbxDouble3 rotation = pNode->LclRotation.Get();
    double rot_d[3] = {rotation[0], rotation[1], rotation[2]};

    FbxDouble3 scaling = pNode->LclScaling.Get();
    double scale_d[3] = {scaling[0], scaling[1], scaling[2]};

    std::cout << std::fixed;

    for (int i = 0; i < depth; i++) std::cout << "  ";
    std::cout << "\tTranslation: (" << trans_d[0] << ", " << trans_d[1] << ", " << trans_d[2] << ")" << std::endl;

    for (int i = 0; i < depth; i++) std::cout << "  ";
    std::cout << "\tRotation: (" << rot_d[0] << ", " << rot_d[1] << ", " << rot_d[2] << ")" << std::endl;

    for (int i = 0; i < depth; i++) std::cout << "  ";
    std::cout << "\tScaling: (" << scale_d[0] << ", " << scale_d[1] << ", " << scale_d[2] << ")" << std::endl;

    auto node = CreateNode(builder, pNode);
    nodes.push_back(node);

    // 子ノードを再帰的に処理
    int childCount = pNode->GetChildCount();
    for (int i = 0; i < childCount; i++) {
        IncludeNode(builder, nodes, pNode->GetChild(i), depth + 1);
    }
}

int main() {
    flatbuffers::FlatBufferBuilder  builder(1024);

    FbxManager* manager = FbxManager::Create();
    FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT);
    manager->SetIOSettings(ios);

    FbxImporter* importer = FbxImporter::Create(manager, "");

    std::filesystem::path relativePath("dragon.fbx");
//    std::filesystem::path currentPath = std::filesystem::current_path().parent_path();
//    std::filesystem::path fbxPath = currentPath / relativePath;

    std::filesystem::path fbxPath = std::filesystem::canonical(relativePath);

    if (!importer->Initialize(fbxPath.string().c_str(), -1, manager->GetIOSettings())){
        std::cerr << "Failed to initialize FBX importer: " << importer->GetStatus().GetErrorString() << std::endl;
        return 1;
    }

    FbxScene* scene = FbxScene::Create(manager, "Scene");
    importer->Import(scene);
    importer->Destroy();

    FbxNode* rootNode = scene->GetRootNode();

    std::vector<flatbuffers::Offset<Node>> nodes;
    if (rootNode){
        for (int i =0; i < rootNode->GetChildCount(); i++){
            IncludeNode(builder, nodes, rootNode->GetChild(i));
        }
    }
    manager->Destroy();

    auto f_nodes = builder.CreateVector(nodes);
    auto hierarchy = CreateHierarchy(builder, f_nodes);

    FinishHierarchyBuffer(builder, hierarchy);

    uint8_t * buf = builder.GetBufferPointer();
    size_t size = builder.GetSize();

    ofstream fout;
    fout.open("sample.hcw", ios::out|ios::binary|ios::trunc);
    if (!fout){
        return 1;
    }

    fout.write((char*)buf, size);
    fout.close();

    return 0;
}