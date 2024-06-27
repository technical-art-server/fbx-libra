#include <iostream>
#include "VertexCounterWeight.h"
#include "VertexCounterWeightFactory.h"
#include "../FlatBufferLoader.h"

using namespace std;
using namespace FbxLibra::CounterWeight;

CounterWeight* VertexCounterWeightFactory::CreateCounterWeight(const std::filesystem::path& fbx_path) {
	FbxManager* manager = FbxManager::Create();
	FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(ios);

	FbxImporter* importer = FbxImporter::Create(manager, "");

	if (!importer->Initialize(fbx_path.string().c_str(), -1, manager->GetIOSettings())) {
		std::cerr << "Failed to initialize FBX importer: " << importer->GetStatus().GetErrorString() << std::endl;
		return nullptr;
	}

	FbxScene* scene = FbxScene::Create(manager, "Scene");
	importer->Import(scene);

	FbxNode* rootNode = scene->GetRootNode();

	//scene内のMeshノードを取得
	std::vector<FbxNode*> mesh_nodes;
	if (rootNode) {
		for (int i = 0; i < rootNode->GetChildCount(); i++) {
			IncludeMeshNodes(rootNode->GetChild(i), mesh_nodes);
		}
	}

	if (mesh_nodes.empty()) {
		std::cerr << "No mesh nodes found in the scene." << std::endl;
		return nullptr;
	}

	std::vector<flatbuffers::Offset<MeshNode>> mesh_node_vector;

	// Loop of mesh nodes
	for (auto node : mesh_nodes) {
		auto mesh = node->GetMesh();
		if (!mesh) {
			std::cerr << "Failed to get mesh from node: " << node->GetName() << std::endl;
			continue;
		}

		//頂点の座標を取得
		int vertex_count = mesh->GetControlPointsCount();
		FbxVector4* vertices = mesh->GetControlPoints();

		std::vector<Vector3> vertices_vector;

		for (int i = 0; i < vertex_count; ++i) {
			auto vertex = vertices[i];
			auto v_pos = Vector3(vertex[0], vertex[1], vertex[2]);
			vertices_vector.push_back(v_pos);
		}

		auto vertices_offsets = builder->CreateVectorOfStructs(vertices_vector);

		//頂点のインデックスを取得
		int polygon_count = mesh->GetPolygonCount();
		std::vector<int> indices;

		for (int i = 0; i < polygon_count; ++i) {
			int polygon_size = mesh->GetPolygonSize(i);
			for (int j = 0; j < polygon_size; ++j) {
				indices.push_back(mesh->GetPolygonVertex(i, j));
			}
		}

		auto indices_offsets = builder->CreateVector(indices);


		//メッシュのUVを取得
		int uv_count = mesh->GetElementUVCount();
		FbxGeometryElementUV* uv = mesh->GetElementUV(0);

		std::vector<Vector2> uv_vector;

		// UVがない場合はnullチェックではじく
		if (uv) {
			for (int i = 0; i < uv_count; ++i) {
				auto uv_value = uv->GetDirectArray().GetAt(i);
				auto uv_pos = Vector2(uv_value[0], uv_value[1]);
				uv_vector.push_back(uv_pos);
			}
		}

		auto uv_offsets = builder->CreateVectorOfStructs(uv_vector);


		//メッシュの法線を取得
		int normal_count = mesh->GetElementNormalCount();
		FbxGeometryElementNormal* normal_element = mesh->GetElementNormal(0);

		std::vector<Vector3> normal_vector;

		// 法線がない場合はnullチェックではじく
		if (normal_element) {
			for (int i = 0; i < normal_count; ++i) {
				auto normal_value = normal_element->GetDirectArray().GetAt(i);
				auto normal = Vector3(normal_value[0], normal_value[1], normal_value[2]);
				normal_vector.push_back(normal);
			}
		}

		auto normal_offsets = builder->CreateVectorOfStructs(normal_vector);

		cout << "Mesh Name: " << node->GetName() << endl;
		cout << "Vertex Count: " << vertex_count << endl;

		auto mesh_offset = CreateMesh(
			*this->builder, vertices_offsets, uv_offsets, indices_offsets, normal_offsets);

		auto mesh_name = this->builder->CreateString(node->GetName());
		auto fbx_pos = node->LclTranslation.Get();
		auto fbx_rot = node->LclRotation.Get();
		auto fbx_scl = node->LclScaling.Get();

		auto position = Vector3(fbx_pos[0], fbx_pos[1], fbx_pos[2]);
		auto rotation = Vector3(fbx_rot[0], fbx_rot[1], fbx_rot[2]);
		auto scale = Vector3(fbx_scl[0], fbx_scl[1], fbx_scl[2]);


		auto transform = CreateTransform(*this->builder, &position, &rotation, &scale);
		auto mesh_node = CreateMeshNode(*this->builder, mesh_name, transform, mesh_offset);

		mesh_node_vector.push_back(mesh_node);
	} // ends of Loop of mesh nodes


	auto mesh_nodes_offsets = builder->CreateVector(mesh_node_vector);
	auto meshes_offsets = CreateMeshes(*this->builder, mesh_nodes_offsets);
	//Finish serializing a buffer by writing the root offset.
	FinishMeshesBuffer(*builder, meshes_offsets);

	auto ne = GetMeshes(builder->GetBufferPointer());

	importer->Destroy();
	scene->Destroy();
	ios->Destroy();
	manager->Destroy();

	return new VertexCounterWeight(ne);;
}

// シーン内のMeshノードを再帰的に探索する関数
void VertexCounterWeightFactory::IncludeMeshNodes(FbxNode* node, std::vector<FbxNode*>& parentNodes) {

	if (node->GetNodeAttribute()) {
		auto attr = node->GetNodeAttribute()->GetAttributeType();
		if (attr == FbxNodeAttribute::eMesh) {
			parentNodes.push_back(node);
		}
	}

	for (int i = 0; i < node->GetChildCount(); ++i) {
		IncludeMeshNodes(node->GetChild(i), parentNodes);
	}
}


CounterWeight* VertexCounterWeightFactory::LoadCounterWeight(const std::filesystem::path& weight_path) {
	auto weight = FlatBufferLoader::Load(weight_path.string().c_str(), GetMeshes);
	return new VertexCounterWeight(weight);
}