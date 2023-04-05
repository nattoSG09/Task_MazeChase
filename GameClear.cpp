#include "GameClear.h"
#include"Global.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
GameClear::GameClear(GameObject* parent)
	: GameObject(parent, "GameClear"),pCoin(nullptr)
{
}

//������
void GameClear::Initialize()
{
	hPict_ = Image::Load("P_GameClearTest.png");
	assert(hPict_ >= 0);

	pCoin = new Text;

	pCoin->Initialize();

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
	pCoin->Draw(180,290, Global::Coin);
	transform_.scale_ = { 0.67f,0.67f,0.67f };
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);


}

//�J��
void GameClear::Release()
{
}