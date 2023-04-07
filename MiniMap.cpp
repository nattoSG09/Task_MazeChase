#include "MiniMap.h"

const float MapSTDPosX = -0.98f;
const float MapSTDPosY = 0.158f;

/*--------------MiniMapObjectクラスの説明--------------
・画面端にミニマップを配置する
・16*16のサイズまでのCSVデータを
---------------------------------------------*/

//コンストラクタ
MiniMap::MiniMap(GameObject* parent)
	: GameObject(parent, "MiniMap"), hPict_{}, obj_(0),Width_(0),Height_(0),Width_Max(0),Height_Max(0)
	,type_(0),Ppos(0,0,0),DrawX_(0),DrawY_(0),Opasity_(0),Size_(0)
{
}

//初期化
void MiniMap::Initialize()
{
	//table情報の取得
	{
		StageMap* pStageMap = (StageMap*)FindObject("StageMap");
		ptable_ = pStageMap->GetTable_();
		Width_Max = pStageMap->GetWidth();
		Height_Max = pStageMap->GetHeight();
	}
	
	//仮置き
	#if 0
	{
		MiniMapCSV.Load("M_Map1.csv");//マップデータ読み込み

		Width_Max = MiniMapCSV.GetWidth();//CSVの横、縦の要素数を取得
		Height_Max = MiniMapCSV.GetHeight();

		ptable_.resize(Width_Max, vector<int>(Height_Max, 0));//初期化

		for (int x = 0; x < Width_Max; x++)//CSVデータを2次元配列table_に代入
			for (int y = 0; y < Height_Max; y++)
				ptable_[x][y] = MiniMapCSV.GetValue(x, ((Height_Max - 1) - y));
	}
	#endif

	//画像データのロード
	{
		const char* fileName[] = { "P_MapFloor.png","P_MapWall.png","P_MapPlayer.png" };
		for (int i = 0; i < Mini_MAX; i++)
		{
			hPict_[i] = Image::Load(fileName[i]);
			assert(hPict_[i] >= 0);
		}
	}
	
	//画像データ設定
	{
		MapTrans.scale_ = { 0.015f,0.015f,0.015f };
		PlaTrans.scale_ = { 0.0125f,0.0125f,0.0125f };
		PlaTrans.position_ = { -0.96f,0.18f,0.0f };
	}
}

//更新
void MiniMap::Update()
{
}

//描画
void MiniMap::Draw()
{
	//player情報の取得
	{
		Player* p = (Player*)FindObject("Player");
		Ppos.x = p->GetPosition().x;
		Ppos.y = p->GetPosition().z;
	}

	//ミニマップを表示
	{
		for (Width_ = 0; Width_ < Width_Max; Width_++)//横
		{
			for (Height_ = 0; Height_ < Height_Max; Height_++)//縦
			{

				MapTrans.position_.x = (Width_ * 0.025f) + MapSTDPosX;
				MapTrans.position_.y = (Height_ * 0.048f) + MapSTDPosY;

				//いま何行目か*どれくらい間隔開けるか - 初期値

				type_ = ptable_[Width_][Height_];

				Image::SetTransform(hPict_[type_], MapTrans);
				Image::Draw(hPict_[type_]);
			}
		}

	PlaTrans.position_.x = ((Ppos.x - (3 - 0.97)) * 0.0125f) - 0.97f;
	PlaTrans.position_.y = ((Ppos.y - (3 - 0.2 )) * 0.024f ) + 0.2f;
	
	//((Playerの位置-(3-位置))*加速度)±位置
	}
	
	//Playerを表示
	Image::SetTransform(hPict_[2], PlaTrans);
	Image::Draw(hPict_[2]);
}

//開放
void MiniMap::Release()
{
}

//画面上での表示場所を決める関数
void MiniMap::DrawPosition(int _posX, int _posY)
{
	this->DrawX_ = _posX;
	this->DrawY_ = _posY;
}

//画面上での表示サイズを決める関数
void MiniMap::DrawSize(float _size)
{
	this->Size_ = _size;
}

//不透明度を変更する関数
void MiniMap::ChengeOpacity(int _Opa)
{
	this->Opasity_ = _Opa;
}
