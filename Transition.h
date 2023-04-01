#pragma once

#include "Engine/GameObject.h"
#include "Engine/Image.h"

enum {
    FADE_IN = 0,
    FADE_OUT = 1,
};

class Transition : public GameObject
{
private:
    int hPict_;  // 画像番号を格納
    int Opacity_;  // 不透明度を格納
    int Move_;  // 動作状態を格納
    bool Active_;

public:
    // コンストラクタ
    Transition(GameObject* parent);

    // 初期化
    void Initialize() override;

    // 更新
    void Update() override;

    // 描画
    void Draw() override;

    // 開放
    void Release() override;

    // フェードインする関数
    void FadeIN();

    // フェードアウトする関数
    void FadeOUT();

    // 画面遷移を開始する関数
    void Start(int move);

    bool isOpacity(int _num);
};
