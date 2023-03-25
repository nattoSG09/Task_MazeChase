#include "Enemy.h"


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

	//stage情報の取得
	pStageMap_ = (StageMap*)FindObject("StageMap");

	//初期位置の設定
	{
		//ランダムスポーンできない
		#if 0
		{
			float spawnX, spawnZ;
			bool ok = false;
			while (ok)
			{
				spawnX = (float)(rand() % 16 + 0) * 2 + 1;//rand() %範囲+最小値;
				spawnZ = (float)(rand() % 16 + 0) * 2 + 1;//rand() %範囲+最小値;

				if (pStageMap_->IsWall(spawnX, spawnZ))
				{
					EnemyTrans_.position_ = { spawnX , 0.0f , spawnZ };
					ok = true;
				}
			}
		}
		#endif

		EnemyTrans_.position_ = { 10.0f,0.0f,10.0f };
		EnemyTrans_.scale_ = { 0.8f,0.8f,0.8f };
		EnemyTrans_.rotate_.y = 0;
		Model::SetAnimFrame(hModel_, 0, 60, 1);
	}

	
}

//更新
void Enemy::Update()
{
	//課題
	{
	//ランダムスポーン処理
	//※(壁に埋まらずに出現するようにする処理)

	//Enemyが壁を認識して、壁にぶつかったら壁をよけて通る処理

	//playerがEnemyの視界に入ったら追従

	//Coriderがなんか付かない
	}
	
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

	//デバック用
	#if 0
	{
		//Playerが壁と接触しているかを確認する
		if (pStageMap_->IsWall(EnemyTrans_.position_.x, EnemyTrans_.position_.z)) {
			Debug::Log("〇", true);
		}
		else {
			Debug::Log("△", true);
		}
	}
	#endif

	//あたり判定の各頂点を構成
	int checkX1, checkX2;
	int checkZ1, checkZ2;

	//あたり判定の処理
	{
		//座標は小数点が入るからそれをintに直しとく
	//右-----------------------------------------
		{
			//頂点１
			checkX1 = (int)(EnemyTrans_.position_.x + 0.2f);
			checkZ1 = (int)(EnemyTrans_.position_.z + 0.1f);
			//頂点２
			checkX2 = (int)(EnemyTrans_.position_.x + 0.2f);
			checkZ2 = (int)(EnemyTrans_.position_.z - 0.1f);

			//衝突しているかどうか
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				EnemyTrans_.position_.x = (float)((int)EnemyTrans_.position_.x) + (1.0f - 0.2f);
			}
		}
		//-------------------------------------------
		//座標は小数点が入るからそれをintに直しとく
		//左-----------------------------------------
		{
			//頂点１
			checkX1 = (int)(EnemyTrans_.position_.x - 0.2f);
			checkZ1 = (int)(EnemyTrans_.position_.z + 0.1f);
			//頂点２
			checkX2 = (int)(EnemyTrans_.position_.x - 0.2f);
			checkZ2 = (int)(EnemyTrans_.position_.z - 0.1f);

			//衝突しているかどうか
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				EnemyTrans_.position_.x = (float)((int)EnemyTrans_.position_.x) + 0.2f;
			}
		}
		//-------------------------------------------
		//座標は小数点が入るからそれをintに直しとく
		//上-----------------------------------------
		{
			//頂点１
			checkX1 = (int)(EnemyTrans_.position_.x + 0.1f);
			checkZ1 = (int)(EnemyTrans_.position_.z + 0.2f);
			//頂点２
			checkX2 = (int)(EnemyTrans_.position_.x - 0.1f);
			checkZ2 = (int)(EnemyTrans_.position_.z + 0.2f);

			//衝突しているかどうか
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				EnemyTrans_.position_.z = (float)((int)EnemyTrans_.position_.z) + (1.0f - 0.2f);
			}
		}
		//-------------------------------------------
		//座標は小数点が入るからそれをintに直しとく
		//下-----------------------------------------
		{
			//頂点１
			checkX1 = (int)(EnemyTrans_.position_.x + 0.1f);
			checkZ1 = (int)(EnemyTrans_.position_.z - 0.2f);
			//頂点２
			checkX2 = (int)(EnemyTrans_.position_.x - 0.1f);
			checkZ2 = (int)(EnemyTrans_.position_.z - 0.2f);
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				EnemyTrans_.position_.z = (float)((int)EnemyTrans_.position_.z) + 0.2f;
			}
		}
		//-------------------------------------------
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