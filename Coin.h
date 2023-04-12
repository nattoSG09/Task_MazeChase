#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"
#include "StageMap.h"

//�e�X�g�V�[�����Ǘ�����N���X
class Coin : public GameObject
{
private:
	int hModel_;
	StageMap* pStageMap_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Coin(GameObject* parent);

	Coin();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};