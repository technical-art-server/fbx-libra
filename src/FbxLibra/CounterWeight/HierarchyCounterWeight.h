//
// Created by Tack2 on 2024/06/03.
//

#ifndef ALL_HIERARCHYCOUNTERWEIGHT_H
#define ALL_HIERARCHYCOUNTERWEIGHT_H

#include <fbxsdk.h>
#include "cw_generated.h"
#include "CounterWeight.h"

class HierarchyCounterWeight: public CounterWeight {

public:
    explicit HierarchyCounterWeight(const Weight::Hierarchy* hierarchy);
    [[nodiscard]] bool EqualCounterWeight(const CounterWeight& other) const override;

private:
    const Weight::Hierarchy* hierarchy;
};

#endif //ALL_HIERARCHYCOUNTERWEIGHT_H
