#pragma once
#include <vector>
using std::vector;
#include"StageMap.h"
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

enum {
	Mini_FLOOR,
	Mini_WALL,
	Mini_PLAYER,
	Mini_MAX,
};

class MiniMapObject : public GameObject
{
	CsvReader MiniMapCSV;
	int hPict_[Mini_MAX];
	int obj_;
	int type_;

	int Width_Max, Height_Max;
	int Width_, Height_;

	StageMap* pStage_ = (StageMap*)FindObject("StageMap");

	Transform MapTrans;

	vector<vector<int>> table_;//ステージ情報を格納する二次元配列
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	MiniMapObject(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//配置するobjectを変更する関数
	void ObjectSet(int _obj) { obj_ = _obj; }
};

