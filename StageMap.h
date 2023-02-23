#pragma once
#include <vector>
using std::vector;

#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"


class StageMap : public GameObject
{
	CsvReader CsvMap_;	
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
};