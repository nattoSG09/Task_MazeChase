#pragma once
#include "Engine/GameObject.h"

enum
{
	TYPE_FLOOR,
	TYPE_WALL,
	TYPE_MAX
};

class Stage :
	public GameObject
{
	//�z��ŕ��������ق����ǂ��I
	int hModel_[TYPE_MAX];	//[]����enum�ɏ�����MAX�ɂ��邱�ƂŁA�z�񐔂������邱�Ƃ��Ȃ�
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

	//�w�肵���ʒu���ʂ�邩�ʂ�Ȃ����𒲂ׂ�
	//�����Fx,z	���ׂ�ʒu
	//�߂�l�F�ʂ�Ȃ���true / �ʂ�Ȃ���false
	bool IsWall(int x, int z);
};