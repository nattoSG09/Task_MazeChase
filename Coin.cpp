#include "Coin.h"

//コンストラクタ
Coin::Coin(GameObject* parent)
	: GameObject(parent, "Coin"),hModel_(-1),pStageMap_(nullptr)
{
}

Coin::Coin(){}

//初期化
void Coin::Initialize()
{
	//モデルのロード
	hModel_ = Model::Load("F_Coin.fbx");
	assert(hModel_ >= 0);

	//コライダー
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
	AddCollider(collision);

	//Scale_size
	transform_.scale_ = { 0.5f,0.5f ,0.5f };

	//rotate
	transform_.rotate_.x = 90;

	//stage情報の取得
	pStageMap_ = (StageMap*)FindObject("StageMap");

	//スポーン位置の設定
	{
		//固定スポーン
		//transform_.position_ = { 11.0f,0.5f,11.0f };

		//ランダムスポーン
		#if 1
		{
			float spawnX = 0.0f, spawnZ = 0.0f;
			bool ok = true;


			//spawnX = (float)(rand() % 16 + 0) * 2 - 1;//rand() %範囲+最小値;
			//spawnZ = (float)(rand() % 16 + 0) * 2 - 1;//rand() %範囲+最小値;

			while (ok)
			{
				if (pStageMap_->IsWall(spawnX, spawnZ)) {
					spawnX = (float)(rand() % 16 + 0) * 2 - 1;//rand() %範囲+最小値;
					spawnZ = (float)(rand() % 16 + 0) * 2 - 1;//rand() %範囲+最小値;
				}
				else {
					break;
				}
			}
			transform_.position_ = { spawnX , 0.5f , spawnZ };
		}
		#endif
	}
}

//更新
void Coin::Update()
{
	//くるくるまわす
	transform_.rotate_.y++;
}

//描画
void Coin::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Coin::Release()
{
}
