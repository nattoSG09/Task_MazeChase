#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

#include "Player.h"

//�e�X�g�V�[�����Ǘ�����N���X
class Enemy : public GameObject
{
private:
	int hModel_;
	Transform EnemyTrans_; //���O�̈ʒu�����i�[����ϐ�
	XMFLOAT3 TargetPosition_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Enemy(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

