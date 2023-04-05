#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

#include "StageMap.h"
#include "StageObject.h"
#include "Player.h"

enum EnemyPattern{
};


//�e�X�g�V�[�����Ǘ�����N���X
class Enemy : public GameObject
{
private:
	int hModel_;
	Transform EnemyTrans_; //���O�̈ʒu�����i�[����ϐ�
	Transform EnemyDestination;	//�G�p�j���̖ړI�n
	XMFLOAT3 TargetPosition_;
	StageMap* pStageMap_;


	bool flag_Find;
	int CoolTime_;
	int wMoveTime;
	float wTargetX , wTargetZ;
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

	//Enemy�̓���F�Ǐ]
	void FollowingMove();

	//Enemy�̓���F�p�j
	void WanderingMove();

	//�ǂƂ̂����蔻�菈��
	void boundaryCheck();
};

