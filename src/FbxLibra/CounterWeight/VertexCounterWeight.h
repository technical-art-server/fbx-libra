#ifndef ALL_VERTEXCOUNTERWEIGHT_H
#define ALL_VERTEXCOUNTERWEIGHT_H

#include <fbxsdk.h>
#include "vcw_generated.h"
#include "CounterWeight.h"

class VertexCounterWeight: public CounterWeight {

public:
    explicit VertexCounterWeight(const FbxLibra::CounterWeight::Meshes* meshes);
    // C2512エラーで入れたデフォルトコンストラクタ。
    // 引数を指定しない場合のコンストラクタが必要らしい。
	VertexCounterWeight() = default;
    [[nodiscard]] bool EqualCounterWeight(const CounterWeight& other) const override;
	
private:
    const FbxLibra::CounterWeight::Meshes* meshes;
};

#endif //ALL_VERTEXCOUNTERWEIGHT_H