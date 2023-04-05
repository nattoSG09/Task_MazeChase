#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"
#include "Engine/Text.h"

//テストシーンを管理するクラス
class GameClear : public GameObject
{
private:
	int hPict_;
	Text* pCoin;
	Transform CoinTransform;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GameClear(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};