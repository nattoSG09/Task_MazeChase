#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Text.h"
#include "Engine/SceneManager.h"
#include "Engine/SphereCollider.h"

#include "Transition.h"
#include "StageMap.h"
#include "Global.h"

enum {
	CAM_FIXED,
	CAM_FPS,
	CAM_MAX,
};

class Player : 
	public GameObject
{
private:

	int hModel_;	//モデル番号
	StageMap *pStageMap_;	//ステージ情報を格納

	XMVECTOR	vPosition_;		//playerのpositionをvector型として格納
	XMVECTOR	vMoveZ_;		//空方向（Ｚ軸）
	XMVECTOR	vMoveX_;		//空方向（Ｘ軸）

	int CamType_;	//カメラ番号
	XMFLOAT3	CamPosition_;	//カメラの位置を格納
	XMFLOAT3	CamTarget_;		//カメラの焦点を格納

	int GetCoin_;	//取得したコインの枚数を格納
	Text* pText;	//スコアを表示するテキスト

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

	//任意のゲームオブジェクトに「何メートル先でぶつかるか」を求める関数
	int GetModelHandle();

	//壁とのあたり判定処理
	void boundaryCheck();

	//コライダーの衝突判定
	void OnCollision(GameObject* pTarget) override;

//カメラ関係ーーーーーーーーーーーー
	//視点を変更する関数
	void CamChange();

	//視点を設定する関数：一人称
	void CamSet_FPS();

	//視点を設定する関数：固定位置からの追従
	void CamSet_FIXED();
};
