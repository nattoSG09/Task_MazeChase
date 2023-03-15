
#include "PlayScene.h"
#include "StageMap.h"
#include"MiniMapObject.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),Time_(nullptr),state_(0)
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<StageMap>(this);
	Instantiate<Player>(this);
	Instantiate<MiniMapObject>(this);
	Camera::SetPosition(XMFLOAT3(7.5, 10, -10));
	Camera::SetTarget(XMFLOAT3(7.5, 2, 3));
	ShowCursor(false);//true -> 表示    false -> 非表示
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