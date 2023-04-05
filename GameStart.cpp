#include "GameStart.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
GameStart::GameStart(GameObject* parent)
	: GameObject(parent, "GameStart"), hPict_(-1)
{
}

//初期化
void GameStart::Initialize()
{
	hPict_ = Image::Load("P_GameStart.png");
	assert(hPict_ >= 0);

	//Transition setting
	transition_ = Instantiate<Transition>(this);


}

//更新
void GameStart::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSm = (SceneManager*)FindObject("SceneManager");
		pSm->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void GameStart::Draw()
{
	//transform_.scale_ = { 0.67f,0.67f ,0.67f };
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
	Image::SetAlpha(hPict_, 255);
}

//開放
void GameStart::Release()
{
}