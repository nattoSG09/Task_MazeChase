
#include "PlayScene.h"


//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),Time_(nullptr),state_(0)
{
}

//初期化
void PlayScene::Initialize()
{
	//Stage setting
	Instantiate<StageMap>(this);

	//Player setting
	Instantiate<Player>(this);

	//Enemy setting
	for (int i = 0; i < 2; i++) {
		Instantiate<Enemy>(this);
	}
	
	//Coin setting
	/*for (int i = 0; i < 30; i++){
		Instantiate<Coin>(this);
	}*/

	//Cursor setting
	ShowCursor(true);//true -> 表示    false -> 非表示

	//MiniMap setting
	#if 1
	{
		MiniMap_ = Instantiate<MiniMap>(this);
		MiniMap_->DrawPosition(0, 0);
		MiniMap_->DrawSize(0.0125f);
		MiniMap_->ChengeOpacity(255);
	}
	#endif

	//Timer setting
	#if 1
	{
		Time_ = Instantiate<Timer>(this);
		Time_->DrawPostion(30, 30);
		Time_->SetLimit(5);	//このゲームの制限時間（秒）
	}
	#endif

	//Transition setting
	transition_ = Instantiate<Transition>(this);
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
	// フェードインを実行
	transition_->Start(FADE_IN);

	state_ = STATE_PLAY;

}

//更新・プレイ中
void PlayScene::UpdatePlay()
{
	//Time_->TimeStart();

	if (Time_->IsFinished()) {
		state_ = STATE_FINISH;
	}
}

//更新・終了
void PlayScene::UpdateFinish()
{

	// フェードアウトを実行
	transition_->Start(FADE_OUT);

	if (transition_->isOpacity(255)) {
		SceneManager* pSm = (SceneManager*)FindObject("SceneManager");
		pSm->ChangeScene(SCENE_ID_CLEAR);
	}
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}