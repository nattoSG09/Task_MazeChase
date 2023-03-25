#include "Enemy.h"
#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"),hModel_(-1),EnemyTrans_(transform_)
{
}

//初期化
void Enemy::Initialize()
{
	hModel_ = Model::Load("F_Enemy(move).fbx");
	assert(hModel_ >= 0);

	//初期位置の設定
	{
		EnemyTrans_.position_ = { 10.0f,0.0f,13.0f };
		EnemyTrans_.scale_ = { 0.8f,0.8f,0.8f };
		EnemyTrans_.rotate_.y = 0;
		Model::SetAnimFrame(hModel_, 0, 60, 1);
	}
}

//更新
void Enemy::Update()
{
	//Enemyの追従処理
	{
		//playerの位置を取得する
		Player* p = (Player*)FindObject("Player");
		TargetPosition_ = p->GetPPos();

		//Enemyとplayerの差を計算する
		XMFLOAT3 deltaPosition = XMFLOAT3(
			TargetPosition_.x - EnemyTrans_.position_.x,
			TargetPosition_.y - EnemyTrans_.position_.y,
			TargetPosition_.z - EnemyTrans_.position_.z
		);

		//Enemyの進行方向を計算する
		XMVECTOR EnemyDir = XMVector3Normalize(XMLoadFloat3(&deltaPosition));

		//Enemyの移動速度
		float Speed = 0.05;

		//EnemyをTargetに向かって移動させる
		EnemyTrans_.position_.x += (XMVectorGetX(EnemyDir) * Speed);
		EnemyTrans_.position_.y += (XMVectorGetY(EnemyDir) * Speed);
		EnemyTrans_.position_.z += (XMVectorGetZ(EnemyDir) * Speed);

		//ベクトルの長さを求める
		XMVECTOR vLength = XMVector3Length(EnemyDir);
		float length = XMVectorGetX(vLength);

		if (length != 0)//vMoveの長さが0じゃないとき(動いているとき)
		{
			XMVECTOR vFront = { 0,0,1,0 };//奥向きのベクトル

			XMVECTOR vDot = XMVector3Dot(vFront, EnemyDir);
			//↑の二つのベクトルの内積を求める
			float dot = XMVectorGetX(vDot);
			float angle = acos(dot);//アークコサインで計算すると"狭い角度"のほうの角度を求める

			XMVECTOR vCross = XMVector3Cross(vFront, EnemyDir);
			//↑二つのベクトルの外積を求める
			//外積のYが０より小さかったら
			if (XMVectorGetY(vCross) < 0) {
				//angleに -1 をかける
				angle *= -1;
			}

			EnemyTrans_.rotate_.y = XMConvertToDegrees(angle);
		}
	}
}

//描画
void Enemy::Draw()
{
	Model::SetTransform(hModel_, EnemyTrans_);
	Model::Draw(hModel_);
}

//開放
void Enemy::Release()
{
}