#include "StageMap.h"
#include "Stage.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"


//�������������������������������FStageMap.cpp�����F��������������������������������������
//�u�X�e�[�W�}�b�v�N���X�v�����͂̏ڍׂ�ݒ肷��N���X�B		
// 
// 
//��������������������������������������������=��������������������������������������������


//�R���X�g���N�^
	//�z��ɂ���ƃR���X�g���N�^�ŏ������̎d�����ς��
	//����Ă邱�Ƃ� int a[2]={1,1} �Ɠ���
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), hModel_{ -1,-1 }, table_(nullptr)
{

	CsvReader csv;		//Web�����Acsv�ǂݍ��݂̍��ڂɏ����Ă�
	csv.Load(".csv");
	width_ = csv.GetWidth();
	height_ = csv.GetHeight();

	table_ = new int* [width_];

	for (int x = 0; x < width_; x++)
	{
		table_[x] = new int[height_];
	}

	for (int x = 0; x < width_; x++)
	{
		for (int z = 0; z < width_; z++)
		{
			table_[x][height_ - 1 - z] = csv.GetValue(x, z);	//z�͏㉺���]���鎮�ɂȂ��Ă�
															//GetValue��(14-z)�ł���
		}
	}

}

//�f�X�g���N�^
Stage::~Stage() {}

void StageMap::Initialize()
{
	const char* fileName[] = { "","","" };	//���f����������z��

	for (int e = 0; e < TYPE_MAX; e++)
	{
		hModel_[e] = Model::Load(fileName[e]);
		assert(hModel_[e] >= 0);
	}

}