#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

class Player : 
	public GameObject
{
private:
	int hModel_;	//���f���ԍ�
	int CamType_;	//�J�����ԍ�

	Transform	PlayerTrans_;	//player��transform���i�[����

	XMFLOAT3	CamPosition_;	//�J�����̈ʒu���i�[����
	XMFLOAT3	CamTarget_;		//�J�����̏œ_���i�[����

	XMVECTOR	vPosition_;		//player��position��vector�^�Ƃ��Ċi�[����
	XMVECTOR	vMoveZ_;		//������i�y���j
	XMVECTOR	vMoveX_;		//������i�w���j
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
};
