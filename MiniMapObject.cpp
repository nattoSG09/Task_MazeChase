#include "MiniMapObject.h"


/*--------------MiniMapObject�N���X�̐���--------------
�E��ʒ[�Ƀ~�j�}�b�v��z�u���� ���܂�ɖ���
�ق��̂Ƃ��낳����ĂȂ����牽������G���[�͂�����K���ɖ��������Ă�����
---------------------------------------------*/

//�R���X�g���N�^
MiniMapObject::MiniMapObject(GameObject* parent)
	: GameObject(parent, "MiniMapObject"), hPict_{ -1,-1,-1 }, obj_(0)
	,Width_(0),Height_(0),Width_Max(0),Height_Max(0),type_(0),Ppos(0,0,0)
{
}

//������
void MiniMapObject::Initialize()
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
void MiniMapObject::Update()
{
	//player���̎擾
	{
		Player* p = (Player*)FindObject("Player");
		Ppos.x = p->GetPPos().x;
		Ppos.y = p->GetPPos().z;
	}

	//PlaTrans.position_.x = (Ppos.x - 2.04*3.82) / 18;
	//PlaTrans.position_.y = (Ppos.y - 2.615 / 2.45  ) / 18;
	//Ppos.x - def *rev / MovSense 
	//PlaTrans.position_.x = ((Ppos.x - 2.04)* -1)*0.01 ;
	//PlaTrans.position_.y = ((Ppos.y - 2.615)*1)*0.01   ;

	PlaTrans.position_.x = ((Ppos.x - 2.04f)*0.0125f) - 0.97f;
	PlaTrans.position_.y = ((Ppos.y - 2.2)*0.0235f) + 0.18f;
	
	//((Player�̈ʒu-(3-�����l))*���傤�ǂ����l)�}platrans�̏����l(�����덷����)
}

//�`��
void MiniMapObject::Draw()
{

	//�~�j�}�b�v��\��
	{
		for (Width_ = 0; Width_ < Width_Max; Width_++)//��
		{
			for (Height_ = 0; Height_ < Height_Max; Height_++)//�c
			{
				/*MapTrans.position_.x = (Width_  * 0.02f)  - 0.98f;
				MapTrans.position_.y = (Height_ * 0.02f)  + 0.378f;*/

				MapTrans.position_.x = (Width_ * 0.025) - 0.98f;
				MapTrans.position_.y = (Height_ * 0.046f) + 0.158f;
				//���܉��s�ڂ�*�ǂꂭ�炢�Ԋu�J���邩 - �����l

				type_ = ptable_[Width_][Height_];

				Image::SetTransform(hPict_[type_], MapTrans);
				Image::Draw(hPict_[type_]);
			}
		}
	}
	
	//Player��\��
	Image::SetTransform(hPict_[2], PlaTrans);
	Image::Draw(hPict_[2]);
}

//�J��
void MiniMapObject::Release()
{
}