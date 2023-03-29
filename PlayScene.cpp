
#include "PlayScene.h"


//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),Time_(nullptr),state_(0)
{
}

//������
void PlayScene::Initialize()
{
	//Stage setting
	Instantiate<StageMap>(this);

	//Player setting
	Instantiate<Player>(this);

	//Enemy setting
	Instantiate<Enemy>(this);

	//Cursor setting
	ShowCursor(true);//true -> �\��    false -> ��\��

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
		Time_->SetLimit(30);	//���̃Q�[���̐������ԁi�b�j
	}
	#endif

	//Transition setting
	//Transition_ = Instantiate<Transition>(this);
}

//�X�V
void PlayScene::Update()
{

	switch (state_)
	{
	case STATE_READY:	UpdateReady(); break;
	case STATE_PLAY:	UpdatePlay(); break;
	case STATE_FINISH:	UpdateFinish(); break;
	}
}

//�X�V�E����
void PlayScene::UpdateReady()
{
	//[Q]�L�[��������...
	if (Input::IsKeyDown(DIK_Q)) {
		state_ = STATE_PLAY;
	}
}

//�X�V�E�v���C��
void PlayScene::UpdatePlay()
{
	Time_->TimeStart();

	if (Time_->IsFinished()) {
		state_ = STATE_FINISH;
	}
}

//�X�V�E�I��
void PlayScene::UpdateFinish()
{
	SceneManager* pSm = (SceneManager*)FindObject("SceneManager");
	pSm->ChangeScene(SCENE_ID_GAMEOVER);
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}