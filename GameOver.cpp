#include "GameOver.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
GameOver::GameOver(GameObject* parent)
	: GameObject(parent, "GameOver"),hPict_(-1),transition_(nullptr)
{
}

//������
void GameOver::Initialize()
{
	hPict_ = Image::Load("p_GameOver.png");
	assert(hPict_ >= 0);

	//Transition setting
	transition_ = Instantiate<Transition>(this);

	
}

//�X�V
void GameOver::Update()
{
	//�t�F�[�h�C�������s
	transition_->Start(FADE_IN);

	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSm = (SceneManager*)FindObject("SceneManager");
		pSm->ChangeScene(SCENE_ID_START);
	}
}

//�`��
void GameOver::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void GameOver::Release()
{
}