#pragma once
#include "Engine/GameObject.h"
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

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};