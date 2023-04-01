#include "GameOver.h"
#include "Engine/Image.h"

//コンストラクタ
GameOver::GameOver(GameObject* parent)
	: GameObject(parent, "GameOver"),hPict_(-1)
{
}

//初期化
void GameOver::Initialize()
{
	/*hPict_ = Image::Load("p_GameOver.png");
	assert(hPict_ >= 0);*/

	//Transition setting
	transition_ = Instantiate<Transition>(this);

	
}

//更新
void GameOver::Update()
{
	//フェードインを実行
	transition_->Start(FADE_IN);
}

//描画
void GameOver::Draw()
{
	/*Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);*/
}

//開放
void GameOver::Release()
{
}