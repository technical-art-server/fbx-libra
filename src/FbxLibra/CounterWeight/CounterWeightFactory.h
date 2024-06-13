//
// Created by Tack2 on 2024/06/13.
//

#ifndef ALL_COUNTERWEIGHTFACTORY_H
#define ALL_COUNTERWEIGHTFACTORY_H


#include "CounterWeight.h"

class CounterWeightFactory {
public:

    CounterWeightFactory();
    virtual ~CounterWeightFactory();
    CounterWeight* Create(const std::string& fbx_path);
    CounterWeight* Load(const std::string& weight_path);

private:
    virtual CounterWeight* CreateCounterWeight(const std::string& fbx_path) = 0;
    virtual CounterWeight* LoadCounterWeight(const std::string& weight_path) = 0;

protected:
    flatbuffers::FlatBufferBuilder* builder;
};


#endif //ALL_COUNTERWEIGHTFACTORY_H
