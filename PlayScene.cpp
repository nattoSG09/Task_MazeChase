
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
	for (int i = 0; i < 2; i++) {
		Instantiate<Enemy>(this);
	}
	
	//Coin setting
	/*for (int i = 0; i < 30; i++){
		Instantiate<Coin>(this);
	}*/

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
		Time_->SetLimit(5);	//���̃Q�[���̐������ԁi�b�j
	}
	#endif

	//Transition setting
	transition_ = Instantiate<Transition>(this);
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
	// �t�F�[�h�C�������s
	transition_->Start(FADE_IN);

	state_ = STATE_PLAY;

}

//�X�V�E�v���C��
void PlayScene::UpdatePlay()
{
	//Time_->TimeStart();

	if (Time_->IsFinished()) {
		state_ = STATE_FINISH;
	}
}

//�X�V�E�I��
void PlayScene::UpdateFinish()
{

	// �t�F�[�h�A�E�g�����s
	transition_->Start(FADE_OUT);

	if (transition_->isOpacity(255)) {
		SceneManager* pSm = (SceneManager*)FindObject("SceneManager");
		pSm->ChangeScene(SCENE_ID_CLEAR);
	}
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}