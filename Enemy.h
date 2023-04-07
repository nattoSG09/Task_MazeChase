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

	//�ǂƂ̏Փ˔��菈��
	void boundaryCheck();

	//n�b����ture��Ԃ��֐�
	bool Every_nMinitues(int n) {return( ((int)FixedTime_ / FPS) % n  == 0);}
};

