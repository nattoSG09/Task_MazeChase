#include "GameOver.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
GameOver::GameOver(GameObject* parent)
	: GameObject(parent, "GameOver"),hPict_(-1),transition_(nullptr)
{
}

//初期化
void GameOver::Initialize()
{
	hPict_ = Image::Load("p_GameOver.png");
	assert(hPict_ >= 0);

	//Transition setting
	transition_ = Instantiate<Transition>(this);

	
}

//更新
void GameOver::Update()
{
	//フェードインを実行
	transition_->Start(FADE_IN);

	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSm = (SceneManager*)FindObject("SceneManager");
		pSm->ChangeScene(SCENE_ID_START);
	}
}

//描画
void GameOver::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void GameOver::Release()
{
}