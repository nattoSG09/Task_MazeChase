#include "MiniMap.h"
#include "Engine/Image.h"
const float MapSTDPosX = -0.98f;
const float MapSTDPosY = 0.158f;

/*--------------MiniMapObject�N���X�̐���--------------
�E��ʒ[�Ƀ~�j�}�b�v��z�u����
�E16*16�̃T�C�Y�܂ł�CSV�f�[�^��
---------------------------------------------*/

//�R���X�g���N�^
MiniMap::MiniMap(GameObject* parent)
	: GameObject(parent, "MiniMap"), hPict_{}, obj_(0),Width_(0),Height_(0),Width_Max(0),Height_Max(0)
	,type_(0),Ppos(0,0,0),Cpos(0, 0, 0),Epos(0, 0, 0),DrawX_(0),DrawY_(0),Opasity_(0),Size_(0)
	,PicSize(0, 0, 0),PicPos(0,0,0)
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
		const char* fileName[] = { "P_MapFloor.png","P_MapWall.png","P_MapPlayer.png","P_Coin2.png","P_Enemy.png"};
		for (int i = 0; i < Mini_MAX; i++)
		{
			hPict_[i] = Image::Load(fileName[i]);
			assert(hPict_[i] >= 0);
		}
	}
	
	//�摜�f�[�^�ݒ�
	{
		PicSize = { 0.0125f,0.0125f,0.0125f };
		PicPos = { -0.96f,0.18f,0.0f };

		MapTrans.scale_ = { 0.015f,0.015f,0.015f };

		PlayerTrans.scale_ = PicSize;
		PlayerTrans.position_ = PicPos;
		
		CoinTrans.scale_ = PicSize;
		CoinTrans.position_ = PicPos;
		
		EnemyTrans.scale_ = PicSize;
		EnemyTrans.position_ = PicPos;
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

	//coin���̎擾
	#if 1
		Coin* c = (Coin*)FindObject("Coin");
		if (c != nullptr) {
			for (int i = 0; i < 30; i++) {
				Cpos = Global::CoinPos[i];
				//Cpos.y = Global::CoinPos.z[i];

				CoinTrans.position_.x = ((Cpos.x - (3 - 0.97)) * 0.0125f) - 0.97f;
				CoinTrans.position_.y = ((Cpos.y - (3 - 0.2)) * 0.024f) + 0.2f;

				//Coin��\��
				//2���ڈȍ~�̕\����������
				Image::SetTransform(hPict_[Mini_COIN], CoinTrans);
				Image::Draw(hPict_[Mini_COIN]);
			}
		}
	#endif
	//enemy���̎擾
	{
		Enemy* e = (Enemy*)FindObject("Enemy");
		Epos.x = e->GetPosition().x;
		Epos.y = e->GetPosition().z;
	}

	//�~�j�}�b�v��\��
	{
		for (Width_ = 0; Width_ < Width_Max; Width_++)//��
		{
			for (Height_ = 0; Height_ < Height_Max; Height_++)//�c
			{
				MapTrans.position_.x = (Width_ * 0.025f) + (MapSTDPosX + (DrawX_ / 10)); 
				MapTrans.position_.y = (Height_ * 0.048f) + (MapSTDPosY + (DrawY_ / 10));

				//���܉��s�ڂ�*�ǂꂭ�炢�Ԋu�J���邩 - �����l

				type_ = ptable_[Width_][Height_];

				Image::SetTransform(hPict_[type_], MapTrans);
				Image::Draw(hPict_[type_]);
			}
		}

	//((Player�̈ʒu-(3-�ʒu))*�����x)�}�ʒu
		PlayerTrans.position_.x = ((Ppos.x - (3 - 0.97)) * 0.0125f) - 0.97f + (DrawX_ / 10);
		PlayerTrans.position_.y = ((Ppos.y - (3 - 0.2)) * 0.024f) + 0.2f + (DrawY_ / 10);

		EnemyTrans.position_.x = ((Epos.x - (3 - 0.97)) * 0.0125f) - 0.97f + (DrawX_ / 10);
		EnemyTrans.position_.y = ((Epos.y - (3 - 0.2)) * 0.024f) + 0.2f + (DrawY_ / 10);

	}
	
	//Player��\��
	Image::SetTransform(hPict_[Mini_PLAYER], PlayerTrans);
	Image::Draw(hPict_[Mini_PLAYER]);

	
		
	//���X�g1������������
	#if 0
	if (c == nullptr) {
		hPict_[Mini_COIN]->KillMe();
	}
	else {
		Image::SetTransform(hPict_[Mini_COIN], CoinTrans);
		Image::Draw(hPict_[Mini_COIN]);
	}
	#endif


	//Enemy��\��
	//Enemy�p�̉摜���~����
	Image::SetTransform(hPict_[Mini_ENEMY], EnemyTrans);
	Image::Draw(hPict_[Mini_ENEMY]);
}

//�J��
void MiniMap::Release()
{
}

//��ʏ�ł̕\���ꏊ�����߂�֐�
void MiniMap::DrawPosition(float _posX, float _posY)
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
