#include "MiniMapObject.h"
#include "Engine/Image.h"
#include "Engine/CsvReader.h"
/*--------------MiniMapObject�N���X�̐���--------------
�E��ʒ[�Ƀ~�j�}�b�v��z�u���� ���܂�ɖ���
�ق��̂Ƃ��낳����ĂȂ����牽������G���[�͂�����K���ɖ��������Ă�����
---------------------------------------------*/

//�R���X�g���N�^
MiniMapObject::MiniMapObject(GameObject* parent)
	: GameObject(parent, "MiniMapObject"), hModel_{ -1,-1,-1 }, obj_(0)
{
}

//������
void MiniMapObject::Initialize()
{
	const char* fileName[] = { "MapFloor.png","MapWall.png","MapPlayer.png" };

	for (int i = 0; i < Mini_MAX; i++)
	{
		hModel_[i] = Image::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}
	transform_.scale_ = { 1,1,1 };
}

//�X�V
void MiniMapObject::Update()
{
}

//�`��
void MiniMapObject::Draw()
{
	Image::SetTransform(hModel_[obj_], transform_);
	Image::Draw(hModel_[obj_]);
}

//�J��
void MiniMapObject::Release()
{
}