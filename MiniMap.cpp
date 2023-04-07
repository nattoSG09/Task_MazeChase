#include "MiniMap.h"

const float MapSTDPosX = -0.98f;
const float MapSTDPosY = 0.158f;

/*--------------MiniMapObject�N���X�̐���--------------
�E��ʒ[�Ƀ~�j�}�b�v��z�u����
�E16*16�̃T�C�Y�܂ł�CSV�f�[�^��
---------------------------------------------*/

//�R���X�g���N�^
MiniMap::MiniMap(GameObject* parent)
	: GameObject(parent, "MiniMap"), hPict_{}, obj_(0),Width_(0),Height_(0),Width_Max(0),Height_Max(0)
	,type_(0),Ppos(0,0,0),DrawX_(0),DrawY_(0),Opasity_(0),Size_(0)
{
}

//������
void MiniMap::Initialize()
{
	//table���̎擾
	{
		StageMap* pStageMap = (StageMap*)FindObject("StageMap");
		ptable_ = pStageMap->GetTable_();
		Width_Max = pStageMap->GetWidth();
		Height_Max = pStageMap->GetHeight();
	}
	
	//���u��
	#if 0
	{
		MiniMapCSV.Load("M_Map1.csv");//�}�b�v�f�[�^�ǂݍ���

		Width_Max = MiniMapCSV.GetWidth();//CSV�̉��A�c�̗v�f�����擾
		Height_Max = MiniMapCSV.GetHeight();

		ptable_.resize(Width_Max, vector<int>(Height_Max, 0));//������

		for (int x = 0; x < Width_Max; x++)//CSV�f�[�^��2�����z��table_�ɑ��
			for (int y = 0; y < Height_Max; y++)
				ptable_[x][y] = MiniMapCSV.GetValue(x, ((Height_Max - 1) - y));
	}
	#endif

	//�摜�f�[�^�̃��[�h
	{
		const char* fileName[] = { "P_MapFloor.png","P_MapWall.png","P_MapPlayer.png" };
		for (int i = 0; i < Mini_MAX; i++)
		{
			hPict_[i] = Image::Load(fileName[i]);
			assert(hPict_[i] >= 0);
		}
	}
	
	//�摜�f�[�^�ݒ�
	{
		MapTrans.scale_ = { 0.015f,0.015f,0.015f };
		PlaTrans.scale_ = { 0.0125f,0.0125f,0.0125f };
		PlaTrans.position_ = { -0.96f,0.18f,0.0f };
	}
}

//�X�V
void MiniMap::Update()
{
}

//�`��
void MiniMap::Draw()
{
	//player���̎擾
	{
		Player* p = (Player*)FindObject("Player");
		Ppos.x = p->GetPosition().x;
		Ppos.y = p->GetPosition().z;
	}

	//�~�j�}�b�v��\��
	{
		for (Width_ = 0; Width_ < Width_Max; Width_++)//��
		{
			for (Height_ = 0; Height_ < Height_Max; Height_++)//�c
			{

				MapTrans.position_.x = (Width_ * 0.025f) + MapSTDPosX;
				MapTrans.position_.y = (Height_ * 0.048f) + MapSTDPosY;

				//���܉��s�ڂ�*�ǂꂭ�炢�Ԋu�J���邩 - �����l

				type_ = ptable_[Width_][Height_];

				Image::SetTransform(hPict_[type_], MapTrans);
				Image::Draw(hPict_[type_]);
			}
		}

	PlaTrans.position_.x = ((Ppos.x - (3 - 0.97)) * 0.0125f) - 0.97f;
	PlaTrans.position_.y = ((Ppos.y - (3 - 0.2 )) * 0.024f ) + 0.2f;
	
	//((Player�̈ʒu-(3-�ʒu))*�����x)�}�ʒu
	}
	
	//Player��\��
	Image::SetTransform(hPict_[2], PlaTrans);
	Image::Draw(hPict_[2]);
}

//�J��
void MiniMap::Release()
{
}

//��ʏ�ł̕\���ꏊ�����߂�֐�
void MiniMap::DrawPosition(int _posX, int _posY)
{
	this->DrawX_ = _posX;
	this->DrawY_ = _posY;
}

//��ʏ�ł̕\���T�C�Y�����߂�֐�
void MiniMap::DrawSize(float _size)
{
	this->Size_ = _size;
}

//�s�����x��ύX����֐�
void MiniMap::ChengeOpacity(int _Opa)
{
	this->Opasity_ = _Opa;
}
