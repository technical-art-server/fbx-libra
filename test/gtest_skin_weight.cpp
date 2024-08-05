#include "gtest/gtest.h"

#include "CounterWeight/SkinWeightCounterWeightFactory.h"
#include <filesystem>
#include "config.h"
#include "FBXLibra.h"

using namespace std;
namespace fs = std::filesystem;

TEST(SkinWeightCounterWeight, Check_SkinWeight_True) {
	SkinWeightCounterWeightFactory factory;
	
	auto dataPath = fs::path(PROJECT_PATH) / "test/data";
	auto fbxPath = dataPath / "fbx/sample_skin_cube.fbx";
	auto weightPath = dataPath / "cw/sample_skin_cube.scw";

	cout << "FBX Path: " << fbxPath << endl;
	cout << "Weight Path: " << weightPath << endl;

	CounterWeight* weight = factory.Load(weightPath);
	CounterWeight* fbx_weight = factory.Create(fbxPath);
	Status result = FBXLibraClient::Weigh(weight, fbx_weight);
	EXPECT_EQ(result, Status::SUCCESS);

	delete weight;
	delete fbx_weight;
}

TEST(SkinWeightCounterWeight, Check_SkinWeight_False) {
	SkinWeightCounterWeightFactory factory;
    
    auto dataPath = fs::path(PROJECT_PATH) / "test/data";
    auto fbxPath = dataPath / "fbx/sample_skin_cube_diff_weight.fbx";
    auto weightPath = dataPath / "cw/sample_skin_cube.vcw";

    cout << "FBX Path: " << fbxPath << endl;
    cout << "Weight Path: " << weightPath << endl;

    CounterWeight* weight = factory.Load(weightPath);
    CounterWeight* fbx_weight = factory.Create(fbxPath);
    Status result = FBXLibraClient::Weigh(weight, fbx_weight);
    EXPECT_EQ(result, Status::FAILURE);

    delete weight;
    delete fbx_weight;
}

TEST(SkinWeightCounterWeight, Check_MultiSKinWeight_True) {
	SkinWeightCounterWeightFactory factory;

	auto dataPath = fs::path(PROJECT_PATH) / "test/data";
	auto fbxPath = dataPath / "fbx/sample_skin_cube_multi.fbx";
	auto weightPath = dataPath / "cw/sample_skin_cube_multi.scw";

	cout << "FBX Path: " << fbxPath << endl;
	cout << "Weight Path: " << weightPath << endl;

	CounterWeight* weight = factory.Load(weightPath);
	CounterWeight* fbx_weight = factory.Create(fbxPath);
	Status result = FBXLibraClient::Weigh(weight, fbx_weight);
	EXPECT_EQ(result, Status::SUCCESS);

	delete weight;
	delete fbx_weight;
}

TEST(SkinWeightCounterWeight, Check_MultiSKinWeight_False) {
	SkinWeightCounterWeightFactory factory;

	auto dataPath = fs::path(PROJECT_PATH) / "test/data";
	auto fbxPath = dataPath / "fbx/sample_skin_cube_multi_diff_weight.fbx";
	auto weightPath = dataPath / "cw/sample_skin_cube_multi.vcw";

	cout << "FBX Path: " << fbxPath << endl;
	cout << "Weight Path: " << weightPath << endl;

	CounterWeight* weight = factory.Load(weightPath);
	CounterWeight* fbx_weight = factory.Create(fbxPath);
	Status result = FBXLibraClient::Weigh(weight, fbx_weight);
	EXPECT_EQ(result, Status::FAILURE);

	delete weight;
	delete fbx_weight;
}


TEST(SkinWeightCounterWeight, Create_SkinWeight) {
    SkinWeightCounterWeightFactory factory;

    auto dataPath = fs::path(PROJECT_PATH) / "test/data";
    auto fbxPath = dataPath / "fbx/sample_skin_cube.fbx";
    auto outputPath = std::filesystem::temp_directory_path() / "sample_skin_cube.hcw";

    factory.Create(fbxPath);
    CounterWeight::Save(*factory.GetBuilder(), outputPath);

    EXPECT_EQ(true, std::filesystem::exists(outputPath));

    // 実際に作って比較してみる
    SkinWeightCounterWeightFactory checkFactory;
    auto weight = checkFactory.Load(outputPath);
    auto fbx_weight = checkFactory.Create(fbxPath);
    Status result = FBXLibraClient::Weigh(weight, fbx_weight);

    EXPECT_EQ(result, Status::SUCCESS);
}