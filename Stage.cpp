#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"


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

//������
void Stage::Initialize()
{

	const char* fileName[] = { "","" };	//���f����������z��

	for (int e = 0; e < TYPE_MAX; e++)
	{
		hModel_[e] = Model::Load(fileName[e]);
		assert(hModel_[e] >= 0);
	}
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
	//transform_�𓮂����ƃX�e�[�W�I�u�W�F�N�g���Ɠ������ߗǂ��Ȃ�
	Transform blockTrans;	//�Ȃ̂�Transform�^�ŐV�����ϐ������K�v������
	for (int x = 0; x < width_; x++)
	{

		for (int z = 0; z < height_; z++)
		{
			blockTrans.position_.x = x;
			blockTrans.position_.z = z;

			int type = table_[x][z];
			Model::SetTransform(hModel_[type], blockTrans);
			Model::Draw(hModel_[type]);

		}
	}
}

//�J��
void Stage::Release()
{
	for (int x = 0; x < width_; x++)
	{
		delete[] table_[x];
	}
	delete[] table_;
}

//
bool Stage::IsWall(int x, int z)
{
	return(table_[x][z] == TYPE_WALL);
}