#pragma once
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

#include "StageMap.h"
#include "StageObject.h"
#include "Player.h"

const int FPS = 60;//フレームレート

class Enemy : public GameObject
{
private:
	int hModel_;//モデル番号
	StageMap* pStageMap_;	//ステージ情報を格納

	XMFLOAT3 F_TargetPosition_;//追従時のターゲット座標を格納
	XMFLOAT3 W_TargetPosition_;//徘徊時のターゲット座標を格納

	bool flag_Find;		//感知状態を格納
	int	CoolTime_;		//見失う時間を格納
	float FixedTime_;	//再ターゲットする時間を格納


	//仮データ(ダイクストラ法を用いた処理の為、一時的に追加中)
	XMFLOAT3 F_TargetPos;
	XMFLOAT3 WayPoint;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Enemy(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	// original function ー－－－－－－－－－

	//２つの座標を比較する関数
	bool isCloser(XMFLOAT3 A_, XMFLOAT3 B_, XMFLOAT3 T_);

	//４つの座標を比較して、最も目的地に近い場所を返す関数
	XMFLOAT3 FindShortestDistance(XMFLOAT3 n, XMFLOAT3 s, XMFLOAT3 e, XMFLOAT3 w, XMFLOAT3 Target);

	//進行する目的地を決定する場所を返す関数
	XMFLOAT3 DIJKSTRA(XMFLOAT3 NowPos, XMFLOAT3 TargetPos);

	//目的地に到着したらTrueを返す関数
	bool isArrival(XMFLOAT3 NowPos_, XMFLOAT3 TargetPos_);

	//Enemyの動作：追従
	void FollowingMove();

	//Enemyの動作：徘徊
	void WanderingMove();

	//壁との衝突判定処理
	void boundaryCheck();

	//n秒事にtureを返す関数
	bool Every_nMinitues(int n) {return( ((int)FixedTime_ / FPS) % n  == 0);}
};

