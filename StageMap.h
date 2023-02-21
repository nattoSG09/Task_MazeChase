#pragma once
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

class StageMap : public GameObject
{
	CsvReader CsvMap_;	//CSVデータを格納
	int Width;			//CSVから読み取った横幅を格納
	int Height;			//CSVから読み取った縦幅を格納
	int** table_;		//ステージ情報を格納
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