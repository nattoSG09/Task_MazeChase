#pragma once
#include <vector>
using std::vector;

#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

class MiniMap : public GameObject
{
	int MiniWidth_;
	int MiniHeight_;

	int hModel_;
	int obj_;



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