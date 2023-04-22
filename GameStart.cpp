#include "GameStart.h"
//�R���X�g���N�^
GameStart::GameStart(GameObject* parent)
	: GameObject(parent, "GameStart"), hPict_(-1), transition_(nullptr), camChange_(0), isFadeNow(false)
{
}

//������
void GameStart::Initialize()
{
	hPict_ = Image::Load("P_GameStart.png");
	assert(hPict_ >= 0);

	//Transition setting
	transition_ = Instantiate<Transition>(this);


}

//�X�V
void GameStart::Update()
{
	//�t�F�[�h�A�E�g���Ă��邩�𔻒f
	if (isFadeNow) {
		transition_->Start(FADE_OUT);

		if (transition_->isOpacity(255)) {
			SceneManager* pSm = (SceneManager*)FindObject("SceneManager");
			pSm->ChangeScene(SCENE_ID_PLAY);
		}
	}
	else {
		if (Input::IsKeyDown(DIK_SPACE)) {
			isFadeNow = true;
		}
	}

	
		
	
}

//�`��
void GameStart::Draw()
{
	//transform_.scale_ = { 0.67f,0.67f ,0.67f };
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
	Image::SetAlpha(hPict_, 255);
}

//�J��
void GameStart::Release()
{
}