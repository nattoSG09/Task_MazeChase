#pragma once
#include "Engine/GameObject.h"


//テストシーンを管理するクラス
class MiniMap : public GameObject
{
private:
	int hMapFloor_;    //画像番号
	int hMapWall_;
	int hMapPlayer_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	MiniMap(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

