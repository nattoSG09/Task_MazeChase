#include "Transition.h"

// コンストラクタ
Transition::Transition(GameObject* parent)
    : GameObject(parent, "Transition"), hPict_(0), Opacity_(0), Move_(0), Active_(false)
{
}

// 初期化
void Transition::Initialize()
{
    // 画像のロード
    hPict_ = Image::Load("P_Transition.png");
    assert(hPict_ >= 0);

    // 不透明度は0から255の数値で管理されている
    Opacity_ = 255;
}

// 更新
void Transition::Update()
{
    switch (Move_)
    {
    case FADE_IN:
        FadeIN();
        break;
    case FADE_OUT:
        FadeOUT();
        break;
    }
}

// 描画
void Transition::Draw()
{
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);
    Image::SetAlpha(hPict_, Opacity_);
}

// 開放
void Transition::Release()
{
}

// フェードインする関数 255->0にする
void Transition::FadeIN()
{
    if (Opacity_ > 0)
    {
        Opacity_ -= 5;
    }
    else
    {
        Opacity_ = 0;
        Move_ = 0;
        Active_ = false;
    }
}

// フェードアウトする関数 0->255にする
void Transition::FadeOUT()
{
    if (Opacity_ < 255)
    {
        Opacity_ += 5;
    }
    else
    {
        Opacity_ = 255;
        Move_ = 0;
        Active_ = false;
    }
}

// 画面遷移を開始する関数
void Transition::Start(int move)
{
    if (!Active_)
    {
        Active_ = true;
        Move_ = move;
    }
}

bool Transition::isOpacity(int _num){
    return (Opacity_ == _num);
}
