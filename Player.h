#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

class Player : 
	public GameObject
{
private:
	int hModel_;            //���f���ԍ�
	float Speed_ = 0.1f;    //Pacman�̑��x���Ǘ�  �����l�̓��f���̔��a�ȉ��ɂ��邱�ƁI(0.3)
	Stage* pStage_;         //�X�e�[�W�N���X�̏�������ϐ�
	XMFLOAT3 prevPosition_; //���O�̈ʒu�����i�[����ϐ�

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
