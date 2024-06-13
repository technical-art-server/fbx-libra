//
// Created by Tack2 on 2024/06/03.
//
#include <iostream>
#include "HierarchyCounterWeight.h"
#include <fbxsdk.h>
#include <fstream>
#include "../FlatBufferLoader.h"


HierarchyCounterWeight::HierarchyCounterWeight(const FbxLibra::CounterWeight::Hierarchy * hierarchy) {
    this->hierarchy = hierarchy;
}

bool HierarchyCounterWeight::EqualCounterWeight(const CounterWeight &other) const {
    auto other_hierarchy = dynamic_cast<const HierarchyCounterWeight*>(&other);

    if (hierarchy == nullptr || other_hierarchy->hierarchy == nullptr) return false;

    auto nodes = hierarchy->nodes();
    auto otherNodes = other_hierarchy->hierarchy->nodes();

    if (nodes->size() != otherNodes->size()) {
        return false;
    }

    for (int i = 0; i < nodes->size(); i++) {
        auto dest_node = nodes->Get(i);
        auto src_node = otherNodes->Get(i);
        if (dest_node->name()->str() != src_node->name()->str()) {
            return false;
        }
        auto dest_transform = dest_node->transform();
        auto src_transform = src_node->transform();
        if (dest_transform->position()->x() != src_transform->position()->x() ||
            dest_transform->position()->y() != src_transform->position()->y() ||
            dest_transform->position()->z() != src_transform->position()->z()) {
            return false;
        }
        if (dest_transform->rotation()->x() != src_transform->rotation()->x() ||
            dest_transform->rotation()->y() != src_transform->rotation()->y() ||
            dest_transform->rotation()->z() != src_transform->rotation()->z()) {
            return false;
        }
        if (dest_transform->scale()->x() != src_transform->scale()->x() ||
            dest_transform->scale()->y() != src_transform->scale()->y() ||
            dest_transform->scale()->z() != src_transform->scale()->z()) {
            return false;
        }
    }

    return true;
}
