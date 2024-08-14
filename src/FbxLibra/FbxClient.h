#ifndef FBXCLIENT_H
#define FBXCLIENT_H
#include <filesystem>
#include <iostream>

#include "fbxsdk.h"

class FbxClient {
private:
    FbxNode* root;

    // RAII(Resource Acquisition Is Initialization)を利用してFbxManager, FbxIOSettings, FbxSceneを破棄する
    static void DestroyFbxManager(FbxManager* manager) { manager->Destroy(); }
    static void DestroyFbxIOSettings(FbxIOSettings* ios) { ios->Destroy(); }
    static void DestroyFbxScene(FbxScene* scene) { scene->Destroy(); }

public:
    FbxClient(): root(nullptr),
                 manager(FbxManager::Create(), DestroyFbxManager),
                 ios(FbxIOSettings::Create(manager.get(), IOSROOT), DestroyFbxIOSettings),
                 scene(FbxScene::Create(manager.get(), "Scene"), DestroyFbxScene){}

    std::unique_ptr<FbxManager, void(*)(FbxManager*)> manager;
    std::unique_ptr<FbxIOSettings, void(*)(FbxIOSettings*)> ios;
    std::unique_ptr<FbxScene, void(*)(FbxScene*)> scene;
    bool Load(const std::filesystem::path& fbx_path)
    {
        manager->SetIOSettings(ios.get());
        if (!manager || !ios || !scene) {
            std::cerr << "Failed to create FbxManager, FbxIOSettings, or FbxScene." << std::endl;
            return false;
        }

        FbxImporter* importer = FbxImporter::Create(manager.get(), "");

        if (!importer->Initialize(fbx_path.string().c_str(), -1, manager->GetIOSettings())){
            std::cerr << "Failed to initialize FBX importer: " << importer->GetStatus().GetErrorString() << std::endl;
            return false;
        }
        importer->Import(scene.get());
        importer->Destroy();

        root = scene->GetRootNode();
        return true;
    };
    [[nodiscard]] FbxNode* GetRootNode() const { return root; }
};



#endif //FBXCLIENT_H
