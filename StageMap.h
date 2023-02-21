#pragma once
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

class StageMap : public GameObject
{
	CsvReader CsvMap_;	
	int Width;			
	int Height;			
	int** table_;		
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