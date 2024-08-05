#ifndef ALL_SKINWEIGHT_H
#define ALL_SKINWEIGHT_H


#include "cw_generated.h"
#include "CounterWeight.h"

class SkinWeightCounterWeight : public CounterWeight {
public:
    SkinWeightCounterWeight() = default;
    explicit SkinWeightCounterWeight(const Weight::SkinWeights* skinWeights);
    [[nodiscard]] bool EqualCounterWeight(const CounterWeight& other) const override;
private:
    const Weight::SkinWeights* skinWeights{};
};


#endif //ALL_SKINWEIGHT_H
