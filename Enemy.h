#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

#include "StageMap.h"
#include "StageObject.h"
#include "Player.h"

const int FPS = 60;//�t���[�����[�g

class Enemy : public GameObject
{
private:
	int hModel_;//���f���ԍ�
	StageMap* pStageMap_;	//�X�e�[�W�����i�[

	XMFLOAT3 F_TargetPosition_;//�Ǐ]���̃^�[�Q�b�g���W���i�[
	XMFLOAT3 W_TargetPosition_;//�p�j���̃^�[�Q�b�g���W���i�[

	bool flag_Find;		//���m��Ԃ��i�[
	int	CoolTime_;		//���������Ԃ��i�[
	float FixedTime_;	//�ă^�[�Q�b�g���鎞�Ԃ��i�[


	//���f�[�^(�_�C�N�X�g���@��p���������ׁ̈A�ꎞ�I�ɒǉ���)
	XMFLOAT3 F_TargetPos;
	XMFLOAT3 WayPoint;

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

	// original function �[�|�|�|�|�|�|�|�|�|

	//�Q�̍��W���r����֐�
	bool isCloser(XMFLOAT3 A_, XMFLOAT3 B_, XMFLOAT3 T_);

	//�S�̍��W���r���āA�ł��ړI�n�ɋ߂��ꏊ��Ԃ��֐�
	XMFLOAT3 FindShortestDistance(XMFLOAT3 n, XMFLOAT3 s, XMFLOAT3 e, XMFLOAT3 w, XMFLOAT3 Target);

	//�i�s����ړI�n�����肷��ꏊ��Ԃ��֐�
	XMFLOAT3 DIJKSTRA(XMFLOAT3 NowPos, XMFLOAT3 TargetPos);

	//�ړI�n�ɓ���������True��Ԃ��֐�
	bool isArrival(XMFLOAT3 NowPos_, XMFLOAT3 TargetPos_);

	//Enemy�̓���F�Ǐ]
	void FollowingMove();

	//Enemy�̓���F�p�j
	void WanderingMove();

	//�ǂƂ̏Փ˔��菈��
	void boundaryCheck();

	//n�b����ture��Ԃ��֐�
	bool Every_nMinitues(int n) {return( ((int)FixedTime_ / FPS) % n  == 0);}
};

