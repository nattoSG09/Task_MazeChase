#include "GameClear.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
GameClear::GameClear(GameObject* parent)
	: GameObject(parent, "GameClear")
{
}

//初期化
void GameClear::Initialize()
{
	hPict_ = Image::Load("P_GameClear.png");
	assert(hPict_ >= 0);
}

//更新
void GameClear::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSm = (SceneManager*)FindObject("SceneManager");
		pSm->ChangeScene(SCENE_ID_START);
	}
}

//描画
void GameClear::Draw()
{
	//transform_.scale_ = { 0.67f,0.67f,0.67f };
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void GameClear::Release()
{
}