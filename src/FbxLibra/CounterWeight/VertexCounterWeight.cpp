#include <iostream>
#include "VertexCounterWeight.h"
#include <fbxsdk.h>
#include <fstream>
#include <filesystem>
#include "../FlatBufferLoader.h"

VertexCounterWeight::VertexCounterWeight(const FbxLibra::CounterWeight::Meshes * meshes) {
    this->meshes = meshes;
}

bool VertexCounterWeight::EqualCounterWeight(const CounterWeight &other) const {
    return true;
}