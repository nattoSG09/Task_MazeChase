#include "MiniMapObject.h"
#include "Engine/Image.h"
#include "Engine/CsvReader.h"
/*--------------MiniMapObjectクラスの説明--------------
・画面端にミニマップを配置する あまりに未完
ほかのところさわってないから何かしらエラーはいたら適当に無効化していいよ
---------------------------------------------*/

//コンストラクタ
MiniMapObject::MiniMapObject(GameObject* parent)
	: GameObject(parent, "MiniMapObject"), hPict_{ -1,-1,-1 }, obj_(0),pStage_(nullptr)
	,Width_(0),Height_(0),Width_Max(0),Height_Max(0),type_(0)
{
}

//初期化
void MiniMapObject::Initialize()
{
	MiniMapCSV.Load("Map.csv");

	Width_Max = MiniMapCSV.GetWidth();
	Height_Max = MiniMapCSV.GetHeight();

	table_.resize(Width_Max, vector<int>(Height_Max, 0));

	for (int x = 0; x < Width_Max; x++)
		for (int z = 0; z < Height_Max; z++)
			table_[x][z] = MiniMapCSV.GetValue(x, ((Height_Max - 1) - z));

	const char* fileName[] = { "MapFloor2.png","MapWall2.png","MapPlayer.png" };
	for (int i = 0; i < Mini_MAX; i++)
	{
		hPict_[i] = Image::Load(fileName[i]);
		assert(hPict_[i] >= 0);
	}
	MapTrans.scale_ = { 0.5,0.5,0.5 };
}

//更新
void MiniMapObject::Update()
{
}

//描画
void MiniMapObject::Draw()
{
	for (Width_ = 0; Width_ < Width_Max; Width_++)
	{
		for (Height_ = 0; Height_ < Height_Max; Height_++)
		{
			MapTrans.position_.x = Width_ ;
			MapTrans.position_.z = Height_;

			type_ = table_[Width_][Height_];

			if (Width_ > 1)
			{
				MapTrans.position_.x = -5;
			}
		Image::SetTransform(hPict_[type_], MapTrans);
		Image::Draw(hPict_[type_]);
		}

	}
}

//開放
void MiniMapObject::Release()
{
}