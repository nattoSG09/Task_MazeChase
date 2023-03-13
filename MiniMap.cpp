#include "MiniMap.h"
#include "MiniMapObject.h"
#include "StageMap.h"
#include "Engine/Image.h"
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

/*--------------MiniMapクラスの説明--------------
・画面端にミニマップを配置する あまりに未完
ほかのところさわってないから何かしらエラーはいたら適当に無効化していいよ
---------------------------------------------*/

//コンストラクタ
MiniMap::MiniMap(GameObject* parent)
	: GameObject(parent, "MiniMap")
{
	//StageMap* s = (StageMap*)FindObject("StageMap");

	//MiniMapTable_ = s->GetStageData();

	////配列をMiniWidth_×Heightで初期化
	//MiniMapTable_.resize(MiniWidth_, vector<int>(MiniHeight_, 0));

}

//初期化
void MiniMap::Initialize()
{
}

//更新
void MiniMap::Update()
{
}

//描画
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

//開放
void MiniMap::Release()
{
}