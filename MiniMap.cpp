#include "MiniMap.h"
#include "MiniMapObject.h"
#include "StageMap.h"
#include "Engine/Image.h"
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

/*--------------MiniMap�N���X�̐���--------------
�E��ʒ[�Ƀ~�j�}�b�v��z�u���� ���܂�ɖ���
�ق��̂Ƃ��낳����ĂȂ����牽������G���[�͂�����K���ɖ��������Ă�����
---------------------------------------------*/

//�R���X�g���N�^
MiniMap::MiniMap(GameObject* parent)
	: GameObject(parent, "MiniMap")
{
	//StageMap* s = (StageMap*)FindObject("StageMap");

	//MiniMapTable_ = s->GetStageData();

	////�z���MiniWidth_�~Height�ŏ�����
	//MiniMapTable_.resize(MiniWidth_, vector<int>(MiniHeight_, 0));

}

//������
void MiniMap::Initialize()
{
}

//�X�V
void MiniMap::Update()
{
}

//�`��
void MiniMap::Draw()
{
	//for (int x = 0; x < MiniWidth_; x++)
	//	for (int z = 0; z < MiniHeight_; z++)
	//	{
	//		if (MiniMapTable_[x][z] == 0)
	//		{
	//			MiniMapObject* FLOOR = (MiniMapObject*)FindObject("MiniMapObject");
	//			FLOOR->ObjectSet(Mini_FLOOR);
	//			FLOOR->SetPosition(XMFLOAT3(x * 2, 0, z * 2));

	//			Image::SetTransform(Mini_FLOOR, transform_);
	//			Image::Draw(Mini_FLOOR);
	//		}
	//		else if (MiniMapTable_[x][z] == 1)
	//		{
	//			MiniMapObject* WALL = (MiniMapObject*)FindObject("MiniMapObject");
	//			WALL->ObjectSet(Mini_WALL);
	//			WALL->SetPosition(XMFLOAT3(x * 2, 0, z * 2));


	//			Image::SetTransform(Mini_WALL, transform_);
	//			Image::Draw(Mini_WALL);
	//		}
	//	}
	/*Image::SetTransform(hModel_[Mini_FLOOR], transform_);
	Image::Draw(hModel_[Mini_FLOOR]);*/
}

//�J��
void MiniMap::Release()
{
}