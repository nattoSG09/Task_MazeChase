#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Text.h"
#include "Engine/SceneManager.h"
#include "Engine/SphereCollider.h"

#include "Transition.h"
#include "StageMap.h"
#include "Global.h"

enum {
	CAM_FIXED,
	CAM_FPS,
	CAM_MAX,
};

class Player : 
	public GameObject
{
private:

	int hModel_;	//���f���ԍ�
	StageMap *pStageMap_;	//�X�e�[�W�����i�[

	XMVECTOR	vPosition_;		//player��position��vector�^�Ƃ��Ċi�[
	XMVECTOR	vMoveZ_;		//������i�y���j
	XMVECTOR	vMoveX_;		//������i�w���j

	int CamType_;	//�J�����ԍ�
	XMFLOAT3	CamPosition_;	//�J�����̈ʒu���i�[
	XMFLOAT3	CamTarget_;		//�J�����̏œ_���i�[

	int GetCoin_;	//�擾�����R�C���̖������i�[
	Text* pText;	//�X�R�A��\������e�L�X�g

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�C�ӂ̃Q�[���I�u�W�F�N�g�Ɂu�����[�g����łԂ��邩�v�����߂�֐�
	int GetModelHandle();

	//�ǂƂ̂����蔻�菈��
	void boundaryCheck();

	//�R���C�_�[�̏Փ˔���
	void OnCollision(GameObject* pTarget) override;

//�J�����֌W�[�[�[�[�[�[�[�[�[�[�[�[
	//���_��ύX����֐�
	void CamChange();

	//���_��ݒ肷��֐��F��l��
	void CamSet_FPS();

	//���_��ݒ肷��֐��F�Œ�ʒu����̒Ǐ]
	void CamSet_FIXED();
};
