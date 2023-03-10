#pragma once
#include "Engine/GameObject.h"


//�e�X�g�V�[�����Ǘ�����N���X
class MiniMap : public GameObject
{
private:
	int hMapFloor_;    //�摜�ԍ�
	int hMapWall_;
	int hMapPlayer_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	MiniMap(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

