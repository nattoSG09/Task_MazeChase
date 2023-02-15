
#include "PlayScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	Time_ = Instantiate<Timer>(this);
	Time_->DrawPostion(30, 30);
	Time_->SetLimit(30);	//���̃Q�[���̐������ԁi�b�j
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