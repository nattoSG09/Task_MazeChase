#include "Enemy.h"

const int FPS = 60;

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

	//Enemy初期設定
	{
		//スポーン位置の設定
		{

			//固定スポーン
			//EnemyTrans_.position_ = { 11.0f,0.0f,11.0f };

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
				EnemyTrans_.position_ = { spawnX , 0.0f , spawnZ };
			}
			#endif

		}

		//モデルスケールの設定
		EnemyTrans_.scale_ = { 0.8f,0.8f,0.8f };

		//アニメーションの設定
		Model::SetAnimFrame(hModel_, 0, 60, 1);
	}
}

//更新
void Enemy::Update()
{
	//課題
	{
	//ランダムスポーン処理
	//※(壁に埋まらずに出現するようにする処理) できた

	//Enemyが壁を認識して、壁にぶつかったら壁をよけて通る処理

	//playerがEnemyの視界に入ったら追従

	//Coriderがなんか付かない
	}

	//Enemyの動作処理
	{
		//Player感知処理
		#if 1
		{
			// 敵キャラクターの向きを表すベクトルを取得する

			XMFLOAT3 EnemyDir;
			XMVECTOR vMove = { 0.0f,0.0f,0.1f,0.0f };
			XMMATRIX EnemyTransMatrix = XMMatrixRotationY(XMConvertToRadians(EnemyTrans_.rotate_.y));

			XMStoreFloat3(&EnemyDir, XMVector3TransformCoord(vMove, EnemyTransMatrix));

			Player* pPlayer = (Player*)FindObject("Player");
			int hPlayer = pPlayer->GetModelHandle();

			//レイキャストデータを用意する
			
			//レイキャスト.スタートを用意
			XMFLOAT3 VsPos = { EnemyTrans_.position_.x,EnemyTrans_.position_.y + 1, EnemyTrans_.position_.z, };
			
			//レイキャストデータ(player)
			RayCastData vrPlayer;
			vrPlayer.start = VsPos;   
			vrPlayer.dir = EnemyDir;
			Model::RayCast(hPlayer, &vrPlayer);

			//flag_Findが"false"の間、Enemyの向いている方向にレイキャストを放つ
			if (flag_Find == false)
			{
				if (vrPlayer.hit) {
					//Playerに当たったらflag_Findを"true"にする
					flag_Find = true;
					Debug::Log("o", true);
				}
				else {
					Debug::Log("x", true);
				}
			}

			//一定時間経過でflag_Findを"false"にする(※条件は「一定距離離れる」に変更の可能性あり)
			/*if (flag_Find == true)
			{
				CoolTime_ = 3 * FPS;
				CoolTime_--;
				if (CoolTime_ < 0) {
					flag_Find = false;
				}
			}*/
			//処理としてはあってるけど、今のコードだとenemyが1回Player見つけると
			//目線外せないから機能してないっぽい感じか？これ
		}
		#endif

		//デバッグ用：flag_Find
		#if 1
		{
			if (Input::IsKeyDown(DIK_U)) {
				flag_Find = false;
			}

			if (Input::IsKeyDown(DIK_I)) {
				flag_Find = true;
			}
		}
		#endif

		//条件：Playerを発見したか否か
		if (flag_Find) {
			//Enemyの追従処理
			FollowingMove();
		}
		else {
			//Enemyの徘徊処理
			WanderingMove();
		}
	}

	//デバック用：あたり判定確認
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

	//あたり判定の処理
	boundaryCheck();
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

//Enemyの動作：追従
void Enemy::FollowingMove()
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

//Enemyの動作：徘徊
void Enemy::WanderingMove()
{
		//向いている方向を取得

		//向いている方向にレイキャストを放つ

		//条件：レイキャストが壁に当たるか否か

		//分岐：当たった
		//左右後方３方向にレイキャストを放つ
		//レイキャストが当たらなかった場所に移動(複数箇所の場合、ランダムに移動)

		//分岐：当たらない
		//向いている方向に移動
}

//壁とのあたり判定処理
void Enemy::boundaryCheck()
{
	//あたり判定の各頂点を構成
	int checkX1, checkX2;
	int checkZ1, checkZ2;
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

//メモ：菅原
//※StageObjectクラス内のhModel_[]という変数配列から適切なモデル番号を取得できない
/*
	レイキャストデータ(wall)
		RayCastData vrWall;
		vrWall.start = VsPos;
		vrWall.dir = EnemyDir;
		Model::RayCast(hWall, &vrWall);

		Debug::Log("W->");
		Debug::Log(vrWall.dist,true);
		Debug::Log("P->");
		Debug::Log(vrPlayer.dist,true);

		//flag_Findが"false"の間、Enemyの向いている方向にレイキャストを放つ
	if (flag_Find == false){
		if (vrPlayer.hit && vrPlayer.dist < vrWall.dist) {
			//Playerに当たったらflag_Findを"true"にする
			flag_Find = true;
			Debug::Log("o", true);
		}
		else {
			Debug::Log("x", true);
		}
	}
*/