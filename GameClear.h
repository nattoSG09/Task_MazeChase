#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"
#include "Engine/Text.h"

//�e�X�g�V�[�����Ǘ�����N���X
class GameClear : public GameObject
{
private:
	int hPict_;
	Text* pCoin;
	Transform CoinTransform;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	GameClear(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};