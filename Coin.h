#pragma once
#include "Engine/GameObject.h"
#include "StageMap.h"

//テストシーンを管理するクラス
class Coin : public GameObject
{
private:
	int hModel_;

	StageMap* pStageMap_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Coin(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};