#include <gtest/gtest.h>
#include <FbxLibra.h>
#include "CounterWeight/HierarchyCounterWeight.h"
#include "CounterWeight/HierarchyCounterWeightFactory.h"

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
	weight = factory->Load("dragon.hcw");
	fbx_weight = factory->Create("dragon.fbx");
	Status result = FBXLibraClient::Weigh(weight, fbx_weight);
	EXPECT_EQ(result, Status::SUCCESS);

	delete factory;
	delete weight;
	delete fbx_weight;

}