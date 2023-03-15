#pragma once
#include <vector>
using std::vector;
#include"StageMap.h"
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

enum {
	Mini_FLOOR,
	Mini_WALL,
	Mini_PLAYER,
	Mini_MAX,
};

class MiniMapObject : public GameObject
{
	CsvReader MiniMapCSV;
	int hPict_[Mini_MAX];
	int obj_;
	int type_;

	XMFLOAT3 Ppos;

	float Width_Max, Height_Max;
	float Width_, Height_;

	StageMap* pStage_ = (StageMap*)FindObject("StageMap");

	Transform MapTrans;
	Transform PlaTrans;
	vector<vector<int>> table_;//�X�e�[�W�����i�[����񎟌��z��
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	MiniMapObject(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�z�u����object��ύX����֐�
	void ObjectSet(int _obj) { obj_ = _obj; }
};

