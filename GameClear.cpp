#include "GameClear.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
GameClear::GameClear(GameObject* parent)
	: GameObject(parent, "GameClear")
{
}

//������
void GameClear::Initialize()
{
	hPict_ = Image::Load("P_GameClear.png");
	assert(hPict_ >= 0);
}

//�X�V
void GameClear::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSm = (SceneManager*)FindObject("SceneManager");
		pSm->ChangeScene(SCENE_ID_START);
	}
}

//�`��
void GameClear::Draw()
{
	//transform_.scale_ = { 0.67f,0.67f,0.67f };
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void GameClear::Release()
{
}