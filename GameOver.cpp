#include "GameOver.h"
#include "Engine/Image.h"

//�R���X�g���N�^
GameOver::GameOver(GameObject* parent)
	: GameObject(parent, "GameOver"),hPict_(-1)
{
}

//������
void GameOver::Initialize()
{
	/*hPict_ = Image::Load("p_GameOver.png");
	assert(hPict_ >= 0);*/

	//Transition setting
	transition_ = Instantiate<Transition>(this);

	
}

//�X�V
void GameOver::Update()
{
	//�t�F�[�h�C�������s
	transition_->Start(FADE_IN);
}

//�`��
void GameOver::Draw()
{
	/*Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);*/
}

//�J��
void GameOver::Release()
{
}