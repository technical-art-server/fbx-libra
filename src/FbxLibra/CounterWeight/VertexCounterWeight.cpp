#include <iostream>
#include "VertexCounterWeight.h"
#include <fbxsdk.h>
#include <fstream>
#include <filesystem>
#include "../FlatBufferLoader.h"

using namespace std;
using namespace FbxLibra::CounterWeight;

template<typename T>
bool CompareFlatBuffersVector(const flatbuffers::Vector<T>* vec1, const flatbuffers::Vector<T>* vec2) {
	if (vec1->size() != vec2->size()) {
		return false;
	}
	// memcmpで連続メモリのByte差分の比較をする
	return std::memcmp(vec1->Data(), vec2->Data(), vec1->size() * sizeof(T)) == 0;
}

VertexCounterWeight::VertexCounterWeight(const Meshes* meshes) {
	this->meshes = meshes;
}

bool VertexCounterWeight::EqualCounterWeight(const CounterWeight& other) const {

	auto other_meshes = dynamic_cast<const VertexCounterWeight*>(&other);

	if (meshes == nullptr || other_meshes == nullptr || other_meshes->meshes == nullptr) return false;

	auto mesh_nodes = meshes->nodes();

	if (mesh_nodes->size() != other_meshes->meshes->nodes()->size()) {
		return false;
	}

	for (int i = 0; i < mesh_nodes->size(); i++) {
		auto dest_mesh_node = mesh_nodes->Get(i);
		auto src_mesh_node = other_meshes->meshes->nodes()->Get(i);

		// compare names
		if (dest_mesh_node->name()->str() != src_mesh_node->name()->str()) {
			return false;
		}

		// compare vertex positions
		if (!CompareFlatBuffersVector(dest_mesh_node->mesh()->positions(), src_mesh_node->mesh()->positions())) {
			return false;
		}

		// compare indices
		if (!CompareFlatBuffersVector(dest_mesh_node->mesh()->indices(), src_mesh_node->mesh()->indices())) {
			return false;
		}

		// compare UVs
		if (!CompareFlatBuffersVector(dest_mesh_node->mesh()->uvs(), src_mesh_node->mesh()->uvs())) {
			return false;
		}

		// compare normals
		if (!CompareFlatBuffersVector(dest_mesh_node->mesh()->normals(), src_mesh_node->mesh()->normals())) {
			return false;
		}

	}

	return true;
}