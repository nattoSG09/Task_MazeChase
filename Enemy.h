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

	//Enemyの動作：追従
	void FollowingMove();

	//Enemyの動作：徘徊
	void WanderingMove();

	//壁との衝突判定処理
	void boundaryCheck();

	//n秒事にtureを返す関数
	bool Every_nMinitues(int n) {return( ((int)FixedTime_ / FPS) % n  == 0);}
};

