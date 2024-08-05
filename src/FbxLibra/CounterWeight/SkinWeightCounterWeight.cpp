#include "SkinWeightCounterWeight.h"

SkinWeightCounterWeight::SkinWeightCounterWeight(const Weight::SkinWeights *skinWeights) {
    this->skinWeights = skinWeights;
}

bool SkinWeightCounterWeight::EqualCounterWeight(const CounterWeight &other) const {
    auto other_skinWeight = dynamic_cast<const SkinWeightCounterWeight *>(&other);

    if (other_skinWeight == nullptr || other_skinWeight->skinWeights == nullptr || skinWeights == nullptr) {
        return false;
    }

    auto original_skin_weight = skinWeights->weights();

    if (original_skin_weight->size() != other_skinWeight->skinWeights->weights()->size()) {
        return false;
    }

    for (int i = 0; i < original_skin_weight->size(); i++) {
        auto original_skin_cluster = original_skin_weight->Get(i);
        auto other_skin_cluster = other_skinWeight->skinWeights->weights()->Get(i);


        if (!CompareFlatBuffersVector(original_skin_cluster->clusters(), other_skin_cluster->clusters())) {
            return false;
        }
    }

    return true;
}
