
#include "PlayScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Time_ = Instantiate<Timer>(this);
	Time_->DrawPostion(30, 30);
	Time_->SetLimit(30);	//このゲームの制限時間（秒）
}

//更新
void PlayScene::Update()
{
	switch (state_)
	{
	case STATE_READY:	UpdateReady(); break;
	case STATE_PLAY:	UpdatePlay(); break;
	case STATE_FINISH:	UpdateFinish(); break;
	}
}

//更新・準備
void PlayScene::UpdateReady()
{
	//[Q]キーを押すと...
	if (Input::IsKeyDown(DIK_Q)) {
		state_ = STATE_PLAY;
	}
}

//更新・プレイ中
void PlayScene::UpdatePlay()
{
	Time_->TimeStart();

	if (Time_->IsFinished()) {
		state_ = STATE_FINISH;
	}
}

//更新・終了
void PlayScene::UpdateFinish()
{
	SceneManager* pSm = (SceneManager*)FindObject("SceneManager");
	pSm->ChangeScene(SCENE_ID_GAMEOVER);
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}