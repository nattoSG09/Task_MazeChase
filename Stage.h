#pragma once
#include "Engine/GameObject.h"



class Stage :
	public GameObject
{
private:
	

	//�z��ŕ��������ق����ǂ��I

	int** table_;		//�t���A�̍��W
	int width_, height_;			//�t���A��x,z���W

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage(GameObject* parent);

	//�f�X�g���N�^
	~Stage();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�ϐ�"table"�̃Q�b�^�[
	//int GetTable() { return **table_; }	//�����ꂾ�ƃ|�C���^�S�̂̏��������Ă���

};

