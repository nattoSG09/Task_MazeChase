#include "MiniMapObject.h"
#include "Engine/Image.h"
#include "Engine/CsvReader.h"
/*--------------MiniMapObjectクラスの説明--------------
・画面端にミニマップを配置する あまりに未完
ほかのところさわってないから何かしらエラーはいたら適当に無効化していいよ
---------------------------------------------*/

//コンストラクタ
MiniMapObject::MiniMapObject(GameObject* parent)
	: GameObject(parent, "MiniMapObject"), hModel_{ -1,-1,-1 }, obj_(0)
{
}

//初期化
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

//更新
void MiniMapObject::Update()
{
}

//描画
void MiniMapObject::Draw()
{
	Image::SetTransform(hModel_[obj_], transform_);
	Image::Draw(hModel_[obj_]);
}

//開放
void MiniMapObject::Release()
{
}