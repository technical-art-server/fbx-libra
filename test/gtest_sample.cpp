#include <gtest/gtest.h>
#include <FbxLibra.h>
#include "CounterWeight/HierarchyCounterWeight.h"
#include "CounterWeight/HierarchyCounterWeightFactory.h"
#include <filesystem>
#include "config.h"

using namespace std;

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(HierarchyCounterWeight, Check_Hierarchy_True) {
	CounterWeightFactory* factory;
	CounterWeight* weight;
	CounterWeight* fbx_weight;
	factory = new HierarchyCounterWeightFactory();
	
	// テスト用にCmakeからプロジェクトのパスを取得
	cout << "Project path: " << PROJECT_PATH << endl;

	auto fbxPath = string(PROJECT_PATH) + "/test/data/" + "fbx/dragon.fbx";
	auto weightPath = string(PROJECT_PATH) + "/test/data/" + "cw/dragon.hcw";

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

TEST(HierarchyCounterWeight, Check_Hierarchy_False) {
    CounterWeightFactory* factory;
    CounterWeight* weight;
    CounterWeight* fbx_weight;
    factory = new HierarchyCounterWeightFactory();


    // テスト用にCmakeからプロジェクトのパスを取得
    cout << "Project path: " << PROJECT_PATH << endl;

    auto fbxPath = string(PROJECT_PATH) + "/test/data/" + "fbx/stanford_bunny.fbx";
    auto weightPath = string(PROJECT_PATH) + "/test/data/" + "cw/dragon.hcw";

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