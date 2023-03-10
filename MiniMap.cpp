#include "MiniMap.h"
#include "Engine/Image.h"
/*--------------MiniMapクラスの説明--------------
・画面端にミニマップを配置する あまりに未完
ほかのところさわってないから何かしらエラーはいたら適当に無効化していいよ
---------------------------------------------*/

//コンストラクタ
MiniMap::MiniMap(GameObject* parent)
	: GameObject(parent, "MiniMap"),hMapFloor_(-1),hMapPlayer_(-1),hMapWall_(-1)
{
}

//初期化
void MiniMap::Initialize()
{
	//画像データのロード
	hMapFloor_ = Image::Load("MapFloor.png");
	assert(hMapFloor_ >= 0);
	hMapPlayer_ = Image::Load("MapWall.png");
	assert(hMapPlayer_ >= 0);
	hMapWall_ = Image::Load("MapPlayer.png");
	assert(hMapWall_ >= 0);
}

//更新
void MiniMap::Update()
{
}

//描画
void MiniMap::Draw()
{
	Image::SetTransform(hMapFloor_, transform_);
	Image::Draw(hMapFloor_);
	Image::SetTransform(hMapPlayer_, transform_);
	Image::Draw(hMapPlayer_);
	Image::SetTransform(hMapWall_, transform_);
	Image::Draw(hMapWall_);
}

//開放
void MiniMap::Release()
{
}
