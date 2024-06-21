#include "gtest/gtest.h"

#include "CounterWeight/HierarchyCounterWeight.h"
#include "CounterWeight/HierarchyCounterWeightFactory.h"
#include <filesystem>
#include "config.h"
#include "FBXLibra.h"

TEST(HierarchyCounterWeight, Create_Hierarchy) {
    HierarchyCounterWeightFactory factory;

    // テスト用にCmakeからプロジェクトのパスを取得
    std::cout << "Project path: " << PROJECT_PATH << std::endl;

    auto fbxPath = std::string(PROJECT_PATH) + "/test/data/" + "fbx/dragon.fbx";
    auto outputPath = std::filesystem::temp_directory_path() / "dragon.hcw";

    factory.Create(fbxPath);
    CounterWeight::Save(*factory.GetBuilder(), outputPath);

    EXPECT_EQ(true, std::filesystem::exists(outputPath));

    // 実際に作って比較してみる
    HierarchyCounterWeightFactory checkFactory;
    auto weight = checkFactory.Load(outputPath);
    auto fbx_weight = checkFactory.Create(fbxPath);
    Status result = FBXLibraClient::Weigh(weight, fbx_weight);

    EXPECT_EQ(result, Status::SUCCESS);
}