#include "gtest/gtest.h"

#include "CounterWeight/VertexCounterWeight.h"
#include "CounterWeight/VertexCounterWeightFactory.h"
#include <filesystem>
#include "config.h"
#include "FBXLibra.h"

using namespace std;
namespace fs = std::filesystem;

TEST(VertexCounterWeight, Check_Vertex_True) {
	CounterWeightFactory* factory;
	CounterWeight* weight;
	CounterWeight* fbx_weight;
	factory = new VertexCounterWeightFactory();
	
	auto dataPath = fs::path(PROJECT_PATH) / "test/data";
	auto fbxPath = dataPath / "fbx/sample_primitives.fbx";
	auto weightPath = dataPath / "cw/sample_primitives.vcw";

	cout << "FBX Path: " << fbxPath << endl;
	cout << "Weight Path: " << weightPath << endl;

	weight = factory->Load( weightPath );
	fbx_weight = factory->Create(fbxPath);
	Status result = FBXLibraClient::Weigh(weight, fbx_weight);
	EXPECT_EQ(result, Status::SUCCESS);

	delete factory;
	delete weight;
	delete fbx_weight;
}

TEST(VertexCounterWeight, Check_Vertex_False) {
    CounterWeightFactory* factory;
    CounterWeight* weight;
    CounterWeight* fbx_weight;
    factory = new VertexCounterWeightFactory();
    
    auto dataPath = fs::path(PROJECT_PATH) / "test/data";
    auto fbxPath = dataPath / "fbx/sample_primitives_diff_vertex.fbx";
    auto weightPath = dataPath / "cw/sample_primitives.vcw";

    cout << "FBX Path: " << fbxPath << endl;
    cout << "Weight Path: " << weightPath << endl;

    weight = factory->Load( weightPath );
    fbx_weight = factory->Create(fbxPath);
    Status result = FBXLibraClient::Weigh(weight, fbx_weight);
    EXPECT_EQ(result, Status::FAILURE);

    delete factory;
    delete weight;
    delete fbx_weight;
}

TEST(VertexCounterWeight, Create_Vertex) {
    VertexCounterWeightFactory factory;

    auto dataPath = fs::path(PROJECT_PATH) / "test/data";
    auto fbxPath = dataPath / "fbx/dragon.fbx";
    auto outputPath = std::filesystem::temp_directory_path() / "dragon.hcw";

    factory.Create(fbxPath);
    CounterWeight::Save(*factory.GetBuilder(), outputPath);

    EXPECT_EQ(true, std::filesystem::exists(outputPath));

    // 実際に作って比較してみる
    VertexCounterWeightFactory checkFactory;
    auto weight = checkFactory.Load(outputPath);
    auto fbx_weight = checkFactory.Create(fbxPath);
    Status result = FBXLibraClient::Weigh(weight, fbx_weight);

    EXPECT_EQ(result, Status::SUCCESS);
}