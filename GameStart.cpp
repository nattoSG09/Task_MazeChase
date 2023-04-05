#include "GameStart.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
GameStart::GameStart(GameObject* parent)
	: GameObject(parent, "GameStart"), hPict_(-1)
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
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSm = (SceneManager*)FindObject("SceneManager");
		pSm->ChangeScene(SCENE_ID_PLAY);
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