/*
#include "Transition.h"

//コンストラクタ
Transition::Transition(GameObject* parent)
	: GameObject(parent, "Transition"),hPict_(0),Opacity_(0),Move_(0),Active_(false)
{
}

//初期化
void Transition::Initialize()
{
	//画像のロード
	hPict_ = Image::Load("P_Transition.png");
	assert(hPict_ >= 0);

	//※　Opacity(不透明度)は０から２５５の数値で管理されている。
}

//更新
void Transition::Update()
{
	switch (Move_)
	{
	case FADE_IN:	FadeIN();	 break;
	case FADE_OUT:	FadeOUT();	 break;
	}
}

//描画
void Transition::Draw()
{
	Image::SetTransform(hPict_,transform_);
	Image::Draw(hPict_);
	Image::SetAlpha(hPict_,Opacity_);
}

//開放
void Transition::Release()
{
}

//フェードインする関数
void Transition::FadeIN()
{
	if (Active_) {
		if (Opacity_ > 255) {
			Opacity_++;
		}
		else {
			Active_ = false;
		}
	}
}

//フェードアウトする関数
void Transition::FadeOUT()
{
	if (Active_) {

	}
}

//画面遷移を開始する関数
void Transition::TransStart(int _move)
{
	this->Move_ = _move;
	Active_ = true;
}

*/