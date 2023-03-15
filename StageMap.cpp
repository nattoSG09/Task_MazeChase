#include "StageMap.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "StageObject.h"


//�������������������������������FStageMap.cpp�����F��������������������������������������
//�u�X�e�[�W�}�b�v�N���X�v�����͂̏ڍׂ�ݒ肷��N���X�B		
// 
// 
//��������������������������������������������=��������������������������������������������

//�R���X�g���N�^
StageMap::StageMap(GameObject* parent)
	: GameObject(parent, "StageMap"),hModel_{-1,-1}
{
	CsvMap_.Load("M_SW_Map1.csv");
	
	Width = CsvMap_.GetWidth();
	Height = CsvMap_.GetHeight();

	//�z���Width�~Height�ŏ�����
	table_.resize(Width, vector<int>(Height, 0));

	for (int x = 0; x < Width; x++)
		for (int z = 0; z < Height; z++)
			table_[x][z] = CsvMap_.GetValue(x, ((Height - 1) - z));
}

//������
void StageMap::Initialize()
{
	for (int x = 0; x < Width; x++)
		for (int z = 0; z < Height; z++) {
			if (table_[x][z] == 0) {
				StageObject* FLOOR = Instantiate<StageObject>(GetParent());
				FLOOR->ObjectSet(OBJ_FLOOR);
				FLOOR->SetPosition(XMFLOAT3(x * 2, 0, z * 2));
			}
			else if (table_[x][z] == 1) {
				StageObject* WALL = Instantiate<StageObject>(GetParent());
				WALL->ObjectSet(OBJ_WALL);
				WALL->SetPosition(XMFLOAT3(x * 2, 0, z * 2));
			}
		}
}

//�X�V
void StageMap::Update()
{
}

//�`��
void StageMap::Draw()
{
}

//�J��
void StageMap::Release()
{
	
}

bool StageMap::IsWall(int x, int z)
{
	return(table_[x][z] == OBJ_WALL);
}



/*
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
*/

