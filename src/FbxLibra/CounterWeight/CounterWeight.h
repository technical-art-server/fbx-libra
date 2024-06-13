//
// Created by Tack2 on 2024/06/13.
//

#ifndef ALL_COUNTERWEIGHT_H
#define ALL_COUNTERWEIGHT_H


#include <flatbuffers/flatbuffer_builder.h>

class CounterWeight {
public:
    bool Equal(const CounterWeight& other);

private:
    [[nodiscard]] virtual bool EqualCounterWeight(const CounterWeight& other) const = 0;
};




#endif //ALL_COUNTERWEIGHT_H
