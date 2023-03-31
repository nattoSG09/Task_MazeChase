#pragma once
#include <vector>
using std::vector;

#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"
#include "Engine/Model.h"

#include "StageObject.h"


class StageMap : public GameObject
{
private:
	enum
	{
		TYPE_FLOOR,
		TYPE_WALL,
		TYPE_MAX
	};

	CsvReader CsvMap_;	
	int hModel_[TYPE_MAX];
	int Width;			
	int Height;			

	vector<vector<int>> table_;//�X�e�[�W�����i�[����񎟌��z��
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	StageMap(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	// �w�肵���ʒu���ʂ�邩�ʂ�Ȃ����𒲂ׂ�
	//�����Fx,z	���ׂ�ʒu
	//�߂�l�F�ǁ�true / �ǂ���Ȃ���false
	bool IsWall(int x, int z);

	//table.size & data�𑼏��ɓn���֐�
	vector<vector<int>>& GetTable_() { return(this->table_); }

	//table.Width��n���֐�
	int GetWidth() { return (this->Width); }

	//table.Height��n���֐�
	int GetHeight() { return (this->Height); }

	//�v���[���n���̃A���S���Y���֐�
	bool HasWallBetween(XMFLOAT3 _positionA, XMFLOAT3 _positionB);
};