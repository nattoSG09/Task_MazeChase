
#include "PlayScene.h"


//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),state_(0), Time_(nullptr),MiniMap_(nullptr),transition_(nullptr),i(0)
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
	
	for (int i = 0; i < 30; i++){
		Instantiate<Coin>(this);
		Coin* c = (Coin*)FindObject("Coin");
		Global::CoinPos[i] = c->GetPosition();
	}

	//Cursor setting
	ShowCursor(true);//true -> 表示    false -> 非表示

	//MiniMap setting
	#if 1
	{
		MiniMap_ = Instantiate<MiniMap>(this);
		MiniMap_->DrawPosition(0.8f, 0.0f);
		MiniMap_->DrawSize(0.0125f);
		MiniMap_->ChengeOpacity(255);
	}
	#endif

	//Timer setting
	#if 1
	{
		Time_ = Instantiate<Timer>(this);
		Time_->DrawPostion(30, 30);
		Time_->SetLimit(50);	//このゲームの制限時間（秒）
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

	FixedTime_++;
}

//更新・準備
void PlayScene::UpdateReady()
{
	// フェードインを実行
	transition_->Start(FADE_IN);
	if (transition_->isOpacity(0)) {
		if (nMinitues(1)) {
			if (i == 0)
			{
				//1を表示
			}
			else if (i == 1)
			{
				//2を表示
			}
			else if (i == 3)
			{
				//3を表示
			}
		i++;
		}
		
	}

	if(nMinitues(3))
	state_ = STATE_PLAY;

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