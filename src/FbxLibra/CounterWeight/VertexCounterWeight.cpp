#include <iostream>
#include "VertexCounterWeight.h"
#include <fbxsdk.h>
#include <fstream>
#include <filesystem>
#include "../FlatBufferLoader.h"

using namespace std;
using namespace FbxLibra::CounterWeight;

VertexCounterWeight::VertexCounterWeight(const Meshes * meshes) {
    this->meshes = meshes;
}

bool VertexCounterWeight::EqualCounterWeight(const CounterWeight &other) const {

	auto other_meshes = dynamic_cast<const VertexCounterWeight*>(&other);

	if (meshes == nullptr || other_meshes->meshes == nullptr) return false;

	auto mesh_nodes = meshes->nodes();

	if (mesh_nodes->size() != other_meshes->meshes->nodes()->size()) {
		// Throw an exception
		return false;
	}

	for (int i = 0; i < mesh_nodes->size(); i++) {
		auto dest_mesh_node = mesh_nodes->Get(i);
		auto src_mesh_node = other_meshes->meshes->nodes()->Get(i);

		if (dest_mesh_node->name()->str() != src_mesh_node->name()->str()) {
			return false;
		}

		// compare vertex positions
		auto vertex_positions = dest_mesh_node->mesh()->positions();
		auto other_vertex_positions = src_mesh_node->mesh()->positions();

		if (vertex_positions->size() != other_vertex_positions->size()) {
			return false;
		}

		auto length = vertex_positions->size() * sizeof(Vector3);

		// メモリを直接全部比較する方法アリかも
		if (std::memcmp(vertex_positions, other_vertex_positions, length) != 0) {
			return false;
		}

		//for (int j = 0; j < vertex_positions->size(); j++) {
		//	auto dest_vertex = vertex_positions->Get(j);
		//	auto src_vertex = other_vertex_positions->Get(j);

			//演算子のオーバーロードを使って比較する作戦（失敗寄り）
			//if (dest_vertex != src_vertex) {
			//	return false;
			//}

			// 力技比較
			//bool eq_x = dest_vertex->x() == src_vertex->x();
			//bool eq_y = dest_vertex->y() == src_vertex->y();
			//bool eq_z = dest_vertex->z() == src_vertex->z();

			//if (!(eq_x && eq_y && eq_z)) {
			//	return false;
			//}

		//}

		// compare indices
		auto indices = dest_mesh_node->mesh()->indices();
		auto other_indices = src_mesh_node->mesh()->indices();

		if (indices->size() != other_indices->size()) {
			return false;
		}

		
		if (std::memcmp(indices, other_indices, indices->size() * sizeof(int)) != 0) {
			return false;
		}

		// compare UVs
		auto uvs = dest_mesh_node->mesh()->uvs();
		auto other_uvs = src_mesh_node->mesh()->uvs();

		if (uvs->size() != other_uvs->size()) {
			return false;
		}

		if (std::memcmp(uvs, other_uvs, uvs->size() * sizeof(Vector2)) != 0) {
			return false;
		}

		// compare normals
		auto normals = dest_mesh_node->mesh()->normals();
		auto other_normals = src_mesh_node->mesh()->normals();

		if (normals->size() != other_normals->size()) {
			return false;
		}

		if (std::memcmp(normals, other_normals, normals->size() * sizeof(Vector3)) != 0) {
			return false;
		}

	}

    return true;
}