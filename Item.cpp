#include "Item.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

//コンストラクタ
Item::Item(GameObject* parent)
	: GameObject(parent, "Item"),hModel_(-1)
{
}

//初期化
void Item::Initialize()
{
	//モデルデータのロード
	//hModel_ = Model::Load("");
	//assert(hModel_ >= 0);

	//SphereCollider* Icollision = new SphereCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), 1.0f);
	//AddCollider(Icollision);
}

//更新
void Item::Update()
{
}

//描画
void Item::Draw()
{
	//アイテムの描画
	//Model::SetTransform(hModel_, transform_);
	//Model::Draw(hModel_);
}

//開放
void Item::Release()
{
}


//当たった判定
void Item::OnCollision(GameObject* pTarget)
{
	//プレイヤーと当たった時
	//if (pTarget->GetObjectName() == "Player")
	//{
		//コインを消す
	//	KillMe();
	//}
}
