#pragma once
#include <vector>
using std::vector;

#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"


class StageMap : public GameObject
{
	CsvReader CsvMap_;	
	int Width;			
	int Height;			

	vector<vector<int>> table_;//ステージ情報を格納する二次元配列
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	StageMap(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};