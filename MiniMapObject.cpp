#include "MiniMapObject.h"
#include "Engine/Image.h"
#include "Engine/CsvReader.h"
/*--------------MiniMapObject�N���X�̐���--------------
�E��ʒ[�Ƀ~�j�}�b�v��z�u���� ���܂�ɖ���
�ق��̂Ƃ��낳����ĂȂ����牽������G���[�͂�����K���ɖ��������Ă�����
---------------------------------------------*/

//�R���X�g���N�^
MiniMapObject::MiniMapObject(GameObject* parent)
	: GameObject(parent, "MiniMapObject"), hPict_{ -1,-1,-1 }, obj_(0),pStage_(nullptr)
	,Width_(0),Height_(0),Width_Max(0),Height_Max(0)
{
}

//������
void MiniMapObject::Initialize()
{
	const char* fileName[] = { "MapFloor.png","MapWall.png","MapPlayer.png" };

	for (int i = 0; i < Mini_MAX; i++)
	{
		hPict_[i] = Image::Load(fileName[i]);
		assert(hPict_[i] >= 0);
	}
	transform_.scale_ = { 0.01f,0.01f ,0.01f };

	table_ = pStage_->GetStageData();


	/*Width_Max  = table_.at(0).size();
	Height_Max = table_.size();*/

	
}

//�X�V
void MiniMapObject::Update()
{
}

//�`��
void MiniMapObject::Draw()
{

	Transform MapTrans;
	/*for (int i = 0; i < Mini_MAX; i++)
	{
	Image::SetTransform(hPict_[i], transform_);
	Image::Draw(hPict_[i]);
	}*/


	for (Width_ = 0; Width_ < Width_Max; Width_++)
	{
		for (Height_ = 0; Height_ < Height_Max; Height_++)
		{
			MapTrans.position_.x = Width_;
			MapTrans.position_.z = Height_;

			int type = table_[Width_][Height_];

			Image::SetTransform(hPict_[type], MapTrans);
			Image::Draw(hPict_[type]);

		}
	}

}

//�J��
void MiniMapObject::Release()
{
}