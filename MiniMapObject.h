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
	CsvReader MiniMapCSV; //このクラスでCSVを受け取るための変数
	int hPict_[Mini_MAX]; // Map画像素材 0=floor,1=wall,2=player
	int obj_;//ほかの画像素材を表示する関数につかう変数
	int type_;//Map画像の種類

	XMFLOAT3 Ppos;//Playerの位置

	float Width_Max, Height_Max;//CSVデータの行列の要素数
	float Width_, Height_; //forループ用のイテレータ(?)

	StageMap* pStage_ = (StageMap*)FindObject("StageMap");

	Transform MapTrans;//Mapの位置などを操作するTransform型

	Transform PlaTrans;//Playerの位置などを操作するTransform型

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

