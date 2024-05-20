- FlatBuffer を調査する 
  - FlatBuffer ビルドする 2h
  - 軽く構造体を書いてみる 2h
- FBX から以下を取得する
  - 各フレームごとの情報
    - ノード情報
      - 頂点座標
      - ノード名

## ユースケース
- 背景アセットを比較する
  - ノード階層、名前が合ってるか
  - 適用マテリアルが合ってるか
- キャラクターを比較する
  
- 骨のアニメーションクリップを比較する

## 構造
骨のアニメーションクリップを比較したい時

- ノード
  - トランスフォーム
  - 名前
  - 子供
    - ノード
      - トランスフォーム
      - 名前

アニメーションを確認したい時は、アニメーション中に名前が変わる事はないので、
トランスフォームの変更点だけで良い。

hierarchy
.acw
- AnimationCountWeight
  - fps
  - connections
    - node
      - node
    - node
      - node
  - nodes
    - node
      - name
      - keys
        - key
          - count
          - vertexes
            - vertex
              - number
              - transform

キャラクター比較
.ccw
- CharacterCountWeight
  - [ ] connections
    - node
      - node
  - [ ] nodes
    - node
      - name
      - transform
      - nodeTypes(transform|skeleton)
      - vertexes
        - vertex
          - number
          - transform

  - materials
    - material
      - name
      - texture_path
      - parameter
        - 面倒なので、やらないかも。
  - bind_poses
    - bind_pose
      - Tスタンスが壊れてたりするのは確かに見たいかも


.ecw
- EnvironmentCountWeight
  - connections
    - node
      - node
  - nodes
    - node


比較はどこが間違ってるか欲しい？
例) 
fpsが違う 1) fps -> 30, 2) fps -> 60

階層が違う 1) どこを出す？

中途半端に出すなら、OK NGのみで。
