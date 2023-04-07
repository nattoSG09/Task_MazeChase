#pragma once
#include "Engine/GameObject.h"
#include "Transition.h"

//�e�X�g�V�[�����Ǘ�����N���X
class GameOver : public GameObject
{

	int hPict_;
	Transition* transition_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	GameOver(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};