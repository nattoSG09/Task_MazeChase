#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

class Player : 
	public GameObject
{
private:
	int hModel_;            //モデル番号
	float Speed_ = 0.1f;    //Pacmanの速度を管理  ※数値はモデルの半径以下にすること！(0.3)
	Stage* pStage_;         //ステージクラスの情報を入れる変数
	XMFLOAT3 prevPosition_; //直前の位置情報を格納する変数

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
