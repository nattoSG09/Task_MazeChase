#include "Enemy.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"),hModel_(-1),pStageMap_(nullptr),F_TargetPosition_{},W_TargetPosition_{}
	,flag_Find(0),CoolTime_(0),FixedTime_(0)
{
}

//初期化
void Enemy::Initialize()
{
	hModel_ = Model::Load("F_Enemy(move).fbx");
	assert(hModel_ >= 0);

	BoxCollider* collision = new BoxCollider(XMFLOAT3(0,1,0), XMFLOAT3(1, 2, 1));
	AddCollider(collision);

	//stage情報の取得
	pStageMap_ = (StageMap*)FindObject("StageMap");

	//EnemyTarget設定
	{
		//bool okk=true;
		//while (okk)
		//{
		//	if (pStageMap_->IsWall(wTargetX,wTargetZ)) {
		//		wTargetX = (float)(rand() % 16 + 0) * 2 - 1;//rand() %範囲+最小値;
		//		wTargetZ = (float)(rand() % 16 + 0) * 2 - 1;//rand() %範囲+最小値;
		//	}
		//	else {
		//		okk = false;
		//	}
		//}
	}
	
	//Enemy初期設定
	{
		//スポーン位置の設定
		{

			//固定スポーン
			//transform_.position_ = { 11.0f,0.0f,11.0f };

			//ランダムスポーン
			#if 1
			{
				float spawnX = 0.0f , spawnZ = 0.0f;
				bool ok = true;

				while (ok)
				{
					if (pStageMap_->IsWall(spawnX, spawnZ)) {
						spawnX = (float)(rand() % 16 + 0) * 2 - 1;//rand() %範囲+最小値;
						spawnZ = (float)(rand() % 16 + 0) * 2 - 1;//rand() %範囲+最小値;
					}
					else {
						ok = false;
					}
				}
				transform_.position_ = { spawnX , 0.0f , spawnZ };
			}
			#endif

		}

		//モデルスケールの設定
		transform_.scale_ = { 0.8f,0.8f,0.8f };
		transform_.rotate_.y = rand()/180;

		//アニメーションの設定
		Model::SetAnimFrame(hModel_, 0, 60, 1);
	}

	//Playerを見失うまでの時間を初期化
	CoolTime_ = 3 * FPS;

	//WayPointの初期化
	WayPoint = transform_.position_;
}

//更新
void Enemy::Update()
{
	//課題
	{
	//ランダムスポーン処理
	//※(壁に埋まらずに出現するようにする処理) = クリア！！

	//Enemyが壁を認識して、壁にぶつかったら壁を避けて通る処理 = 難しい 

	//playerがEnemyの視界に入ったら追従 = クリア！！

	//Coriderがなんか付かない = クリア！！
	}

	//時間を更新
	FixedTime_++;

	//Enemyの動作処理
	{
		//Player感知処理
		#if 0
		{
			// 敵キャラクターの向きを表すベクトルを取得する

			XMFLOAT3 EnemyDir;
			XMVECTOR vMove = { 0.0f,0.0f,0.1f,0.0f };
			XMMATRIX EnemyTransMatrix = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

			XMStoreFloat3(&EnemyDir, XMVector3TransformCoord(vMove, EnemyTransMatrix));

			Player* pPlayer = (Player*)FindObject("Player");
			int hPlayer = pPlayer->GetModelHandle();

			StageMap* pStageMap = (StageMap*)FindObject("StageMap");
			
			XMFLOAT3 PlayerPosition_ = pPlayer->GetPosition();
			

			//レイキャスト.スタートを用意
			XMFLOAT3 VsPos = { transform_.position_.x,transform_.position_.y + 1, transform_.position_.z, };
			
			//レイキャストデータ(player)
			RayCastData vrPlayer;
			vrPlayer.start = VsPos;   
			vrPlayer.dir = EnemyDir;
			Model::RayCast(hPlayer, &vrPlayer);

			//デバック用：レイキャストデータ
			#if 0
			{
				Debug::Log("P->");
				Debug::Log(vrPlayer.dist, true);
			}
			#endif

			//flag_Findが"false"の間、Enemyの向いている方向にレイキャストを放つ
			if (flag_Find == false)
			{
				if (vrPlayer.hit && !pStageMap->HasWallBetween(transform_.position_, PlayerPosition_)){
					//trueになることでPlayerを追従する
						flag_Find = true;
				}
				else {
				}
			}

			//一定時間経過でflag_Findを"false"にする(※条件は「一定距離離れる」に変更の可能性あり)
			if (flag_Find == true)
			{
				CoolTime_--;
				if (CoolTime_ < 0) {
					flag_Find = false;
				}
			}
			else {
				CoolTime_ = 10 * FPS;
			}
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
		if (pStageMap_->IsWall(transform_.position_.x, transform_.position_.z)) {
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
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Enemy::Release()
{
}

// original function

//２つの座標を比較する関数
bool Enemy::isCloser(XMFLOAT3 A_, XMFLOAT3 B_, XMFLOAT3 T_)
{
	bool closest = false;
	float disA = (abs(T_.x) + abs(T_.z)) - (abs(A_.x) + abs(A_.z));
	float disB = (abs(T_.x) + abs(T_.z)) - abs(B_.x) + abs(B_.z);

	if (disA < disB) {
		closest = true;
	}
	return (closest);
}

//４つの座標を比較して、最も目的地に近い場所を返す関数
XMFLOAT3 Enemy::FindShortestDistance(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c, XMFLOAT3 d, XMFLOAT3 Target)
{
	XMFLOAT3 closePos = a;
	if (isCloser(b, closePos, Target)) {
		closePos = b;
	}
	if (isCloser(c, closePos, Target)) {
		closePos = c;
	}
	if (isCloser(d, closePos, Target)) {
		closePos = d;
	}

	return (closePos);
}

//進行する目的地を決定する場所を返す関数
XMFLOAT3 Enemy::DIJKSTRA(XMFLOAT3 NowPos_, XMFLOAT3 TargetPos_)
{
	XMFLOAT3 E, W, N, S;
	//右 
	E = { NowPos_.x + 2.0f,0,NowPos_.z };
	//左 
	W = { NowPos_.x - 2.0f,0,NowPos_.z };
	//奥 
	N = { NowPos_.x,0,NowPos_.z + 2.0f };
	//手前 
	S = { NowPos_.x,0,NowPos_.z - 2.0f };

	XMFLOAT3 CclosePos = FindShortestDistance(E, W, N, S, TargetPos_);
	return CclosePos;
}

//目的地に到着したらTrueを返す関数
bool Enemy::isArrival(XMFLOAT3 NowPos_, XMFLOAT3 TargetPos_)
{
	bool Arr = false;
	if (NowPos_.x == TargetPos_.x && NowPos_.z == TargetPos_.z) {
		Arr = true;
	}
	return (Arr);
}

//Enemyの動作：追従
void Enemy::FollowingMove()
{
	

	//ダイクストラ法を用いた追従処理(失敗)
	#if 1
	{
		//メモ
		{	
			//isArraival()関数による到着判断ができてないのかなー
		}

		//目的地を取得(playerの位置)
		Player* p = (Player*)FindObject("Player");
		F_TargetPos = p->GetPosition();

		//経由地にたどりつくまで
		if (!isArrival(transform_.position_, F_TargetPos)) {

			//EnemyとWayPointの差を計算する
			XMFLOAT3 deltaPosition = XMFLOAT3(
				WayPoint.x - transform_.position_.x,
				0,
				WayPoint.z - transform_.position_.z
			);

			//Enemyの進行方向を計算する
			XMVECTOR EnemyDir = XMVector3Normalize(XMLoadFloat3(&deltaPosition));

			//Enemyの移動速度
			float Speed = 0.05f;

			//EnemyをWayPointに向かって移動させる
			transform_.position_.x += (XMVectorGetX(EnemyDir) * Speed);
			transform_.position_.y += (XMVectorGetY(EnemyDir) * Speed);
			transform_.position_.z += (XMVectorGetZ(EnemyDir) * Speed);

			//ベクトルの長さを求める
			XMVECTOR vLength = XMVector3Length(EnemyDir);
			float length = XMVectorGetX(vLength);

			if (length != 0)
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

				transform_.rotate_.y = XMConvertToDegrees(angle);
			}
		}
		//たどり着いたら
		else {
			//TargetPosまでのWayPointを取得
			XMFLOAT3 WayPoint = DIJKSTRA(transform_.position_, F_TargetPos);
		}
	}
	#endif

	//既存の追従処理(現在使用を中止) 23/04/12～
	#if 0
	{
		//playerの位置を取得する
		Player* p = (Player*)FindObject("Player");
		F_TargetPosition_ = p->GetPosition();

		//Enemyとplayerの差を計算する
		XMFLOAT3 deltaPosition = XMFLOAT3(
			F_TargetPosition_.x - transform_.position_.x,
			F_TargetPosition_.y - transform_.position_.y,
			F_TargetPosition_.z - transform_.position_.z
		);

		//Enemyの進行方向を計算する
		XMVECTOR EnemyDir = XMVector3Normalize(XMLoadFloat3(&deltaPosition));

		//Enemyの移動速度
		float Speed = 0.05f;

		//EnemyをTargetに向かって移動させる
		transform_.position_.x += (XMVectorGetX(EnemyDir) * Speed);
		transform_.position_.y += (XMVectorGetY(EnemyDir) * Speed);
		transform_.position_.z += (XMVectorGetZ(EnemyDir) * Speed);

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

			transform_.rotate_.y = XMConvertToDegrees(angle);
		}

	}
	#endif

}

//Enemyの動作：徘徊
void Enemy::WanderingMove()
{
	
	//敵の巡回先を設定
	#if 1
	{
		//目的地の再設定

		float TargetX = 0, TargetZ = 0;
		bool ok = true;

		if (Every_nMinitues(5)){
			while (ok)
			{
				if (pStageMap_->IsWall(TargetX, TargetZ)) {
					Debug::Log("壁だった！", true);
					TargetX = (float)(rand() % 16 + 0) * 2 - 1;//rand() %範囲+最小値;
					TargetZ = (float)(rand() % 16 + 0) * 2 - 1;//rand() %範囲+最小値;
				}
				else {
					ok = false;
				}
			}
			W_TargetPosition_ = { TargetX , 0 ,TargetZ };
			Debug::Log("目的地を再ターゲットしました。", true);
		}
		
	}
	#endif

	//Enemyとplayerの差を計算する
	XMFLOAT3 deltaPosition = XMFLOAT3(
		W_TargetPosition_.x - transform_.position_.x,
		W_TargetPosition_.y - transform_.position_.y,
		W_TargetPosition_.z - transform_.position_.z
	);

	//Enemyの進行方向を計算する
	XMVECTOR EnemyDir = XMVector3Normalize(XMLoadFloat3(&deltaPosition));

	//Enemyの移動速度
	float Speed = 0.04f;

	//EnemyをTargetに向かって移動させる
	transform_.position_.x += (XMVectorGetX(EnemyDir) * Speed);
	transform_.position_.y += (XMVectorGetY(EnemyDir) * Speed);
	transform_.position_.z += (XMVectorGetZ(EnemyDir) * Speed);

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

		transform_.rotate_.y = XMConvertToDegrees(angle);
	}

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
			checkX1 = (int)(transform_.position_.x + 0.2f);
			checkZ1 = (int)(transform_.position_.z + 0.1f);
			//頂点２
			checkX2 = (int)(transform_.position_.x + 0.2f);
			checkZ2 = (int)(transform_.position_.z - 0.1f);

			//衝突しているかどうか
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				transform_.position_.x = (float)((int)transform_.position_.x) + (1.0f - 0.2f);
			}
		}
		//-------------------------------------------
		//座標は小数点が入るからそれをintに直しとく
		//左-----------------------------------------
		{
			//頂点１
			checkX1 = (int)(transform_.position_.x - 0.2f);
			checkZ1 = (int)(transform_.position_.z + 0.1f);
			//頂点２
			checkX2 = (int)(transform_.position_.x - 0.2f);
			checkZ2 = (int)(transform_.position_.z - 0.1f);

			//衝突しているかどうか
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				transform_.position_.x = (float)((int)transform_.position_.x) + 0.2f;
			}
		}
		//-------------------------------------------
		//座標は小数点が入るからそれをintに直しとく
		//上-----------------------------------------
		{
			//頂点１
			checkX1 = (int)(transform_.position_.x + 0.1f);
			checkZ1 = (int)(transform_.position_.z + 0.2f);
			//頂点２
			checkX2 = (int)(transform_.position_.x - 0.1f);
			checkZ2 = (int)(transform_.position_.z + 0.2f);

			//衝突しているかどうか
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				transform_.position_.z = (float)((int)transform_.position_.z) + (1.0f - 0.2f);
			}
		}
		//-------------------------------------------
		//座標は小数点が入るからそれをintに直しとく
		//下-----------------------------------------
		{
			//頂点１
			checkX1 = (int)(transform_.position_.x + 0.1f);
			checkZ1 = (int)(transform_.position_.z - 0.2f);
			//頂点２
			checkX2 = (int)(transform_.position_.x - 0.1f);
			checkZ2 = (int)(transform_.position_.z - 0.2f);
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				transform_.position_.z = (float)((int)transform_.position_.z) + 0.2f;
			}
		}
		//-------------------------------------------
}