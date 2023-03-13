#pragma once
#include <vector>
using std::vector;

#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

class MiniMap : public GameObject
{
	int MiniWidth_;
	int MiniHeight_;

	int hModel_;
	int obj_;



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