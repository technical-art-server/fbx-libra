#include <gtest/gtest.h>
#include <FbxLibra.h>
#include "CounterWeight/HierarchyCounterWeight.h"
#include "CounterWeight/HierarchyCounterWeightFactory.h"
#include <filesystem>

using namespace std;

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(HierarchyCounterWeight, Check_Hierarchy) {
	CounterWeightFactory* factory;
	CounterWeight* weight;
	CounterWeight* fbx_weight;
	factory = new HierarchyCounterWeightFactory();

	// パスを実行ファイルからの相対パスに変更
	filesystem::path relativePath("dragon.fbx");
	// これだとAll.slnからの相対パスになる。
	// テスト用に環境変数を外部から渡す必要がある。
	filesystem::path testDataPath = filesystem::current_path().parent_path().parent_path() / "test\\data";
	cout << "Current path: " << testDataPath << endl;

	filesystem::path fbxPath = testDataPath / "fbx\\dragon.fbx";
	filesystem::path cwPath = testDataPath / "cw\\dragon.hcw";

	weight = factory->Load(cwPath.string());
	fbx_weight = factory->Create(fbxPath.string());
	Status result = FBXLibraClient::Weigh(weight, fbx_weight);
	EXPECT_EQ(result, Status::SUCCESS);

	delete factory;
	delete weight;
	delete fbx_weight;

}