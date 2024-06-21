//
// Created by Tack2 on 2024/06/13.
//

#ifndef ALL_COUNTERWEIGHT_H
#define ALL_COUNTERWEIGHT_H


#include <flatbuffers/flatbuffer_builder.h>
#include "../Status.h"
#include <filesystem>

class CounterWeight {
public:
    /* @fn
     * @brief 比較機能の共通関数。この呼び出しは共通で内部のEqualCounterWeightをそれぞれのCounterWeightで実装する
     * @param other 比較対象のCounterWeight
     * @return 同じであればtrue
     */
    [[nodiscard]]
    bool Equal(const CounterWeight& other);

    static Status Save(flatbuffers::FlatBufferBuilder& builder, const std::filesystem::path& path);
private:
    /* @fn
     * @brief この関数をオーバーライドし、CounterWeight同士を比較する関数を作成する
     * @param other 比較対象のCounterWeight
     * @return 同じであればtrue
     */
    [[nodiscard]] virtual bool EqualCounterWeight(const CounterWeight& other) const = 0;
};




#endif //ALL_COUNTERWEIGHT_H
