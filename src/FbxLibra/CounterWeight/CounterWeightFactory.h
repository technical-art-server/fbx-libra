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
    /* @fn
     * @brief この関数をオーバーライドし、fbxパスを読み込み、任意のCounterWeightを生成する関数を作成する
     * @param fbx_path FBXファイルのパス
     * @return 任意の生成されたCounterWeight
     */
    virtual CounterWeight* CreateCounterWeight(const std::string& fbx_path) = 0;
    /*
     * @fn
     * @brief この関数をオーバーライドし、CounterWeightFileを読み込みCounterWeightを生成する
     */
    virtual CounterWeight* LoadCounterWeight(const std::string& weight_path) = 0;

protected:
    /*
     * @brief FlatBufferBuilderを持つ。丁寧に書くなら別の管理クラスの参照にすべき
     * @var builder
     */
    flatbuffers::FlatBufferBuilder* builder;
};


#endif //ALL_COUNTERWEIGHTFACTORY_H
