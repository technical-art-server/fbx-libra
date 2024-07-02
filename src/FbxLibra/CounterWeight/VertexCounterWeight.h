#ifndef ALL_VERTEXCOUNTERWEIGHT_H
#define ALL_VERTEXCOUNTERWEIGHT_H

#include <fbxsdk.h>
#include "cw_generated.h"
#include "CounterWeight.h"

class VertexCounterWeight: public CounterWeight {

public:
    explicit VertexCounterWeight(const Weight::Meshes* meshes);
    // C2512エラーで入れたデフォルトコンストラクタ。
    // 引数を指定しない場合のコンストラクタが必要らしい。
	VertexCounterWeight() = default;
    [[nodiscard]] bool EqualCounterWeight(const CounterWeight& other) const override;
	
private:
    const Weight::Meshes* meshes;
};

#endif //ALL_VERTEXCOUNTERWEIGHT_H