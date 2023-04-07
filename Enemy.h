#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

#include "StageMap.h"
#include "StageObject.h"
#include "Player.h"

const int FPS = 60;

//�e�X�g�V�[�����Ǘ�����N���X
class Enemy : public GameObject
{
private:
	int hModel_;
	Transform EnemyTrans_; //���O�̈ʒu�����i�[����ϐ�
	//Transform EnemyDestination;	//�G�p�j���̖ړI�n
	XMFLOAT3 F_TargetPosition_;
	XMFLOAT3 W_TargetPosition_;
	StageMap* pStageMap_;


	bool flag_Find;
	int CoolTime_;
	
	//���u��
	float FixedTime;

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

	bool isCollidingWithWall();

	//n�b����ture��Ԃ��֐�
	bool Every_nMinitues(int n) {
		return( ((int)FixedTime / FPS) % n  == 0);
	}

};

