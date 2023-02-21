#include "StageMap.h"
#include "Stage.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "StageObject.h"


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝：StageMap.cpp説明：＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//「ステージマップクラス」ここはの詳細を設定するクラス。		
// 
// 
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝=＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

//コンストラクタ
StageMap::StageMap(GameObject* parent)
	: GameObject(parent, "StageMap")
{
	//───────────────────────────────────────
	//  CSVデータの初期化
	//───────────────────────────────────────
		//CSVデータをロードする
		//for (int i = 0; i < CSVMAX; i++){
	CsvMap_.Load("Map.csv");
	//テーブルの配列の大きさを把握
	Width = CsvMap_.GetWidth();//CSVの横幅を取得
	Height = CsvMap_.GetHeight();//CSVの縦幅を取得

	table_ = new int* [Width];
	for (int x = 0; x < Width; x++) {
		table_[x] = new int[Height];
	}

	for (int x = 0; x < Width; x++)
		for (int z = 0; z < Height; z++)
			table_[x][z] = CsvMap_.GetValue(x, ((Height - 1) - z));
}

//初期化
void StageMap::Initialize()
{
	for (int x = 0; x < Width; x++)
		for (int z = 0; z < Height; z++) {
			if (table_[x][z] == 0) {
				StageObject* FLOOR = Instantiate<StageObject>(GetParent());
				FLOOR->ObjectSet(OBJ_FLOOR);
				FLOOR->SetPosition(XMFLOAT3(x * 2, 0, z * 2));
			}
			else if (table_[x][z] == 1) {
				StageObject* WALL = Instantiate<StageObject>(GetParent());
				WALL->ObjectSet(OBJ_WALL);
				WALL->SetPosition(XMFLOAT3(x * 2, 0, z * 2));
			}
		}
}

//更新
void StageMap::Update()
{
}

//描画
void StageMap::Draw()
{
}

//開放
void StageMap::Release()
{
	//newで作ったものは消す！
	for (int x = 0; x < Width; x++)
	{
		delete[] table_[x];
	}
	delete[] table_;
}

/*
//コンストラクタ
	//配列にするとコンストラクタで初期化の仕方が変わる
	//やってることは int a[2]={1,1} と同じ
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), hModel_{ -1,-1 }, table_(nullptr)
{

	CsvReader csv;		//Web資料、csv読み込みの項目に書いてる
	csv.Load(".csv");
	width_ = csv.GetWidth();
	height_ = csv.GetHeight();

	table_ = new int* [width_];

	for (int x = 0; x < width_; x++)
	{
		table_[x] = new int[height_];
	}

	for (int x = 0; x < width_; x++)
	{
		for (int z = 0; z < width_; z++)
		{
			table_[x][height_ - 1 - z] = csv.GetValue(x, z);	//zは上下反転する式になってる
															//GetValueで(14-z)でも可
		}
	}

}

//デストラクタ
Stage::~Stage() {}

void StageMap::Initialize()
{
	const char* fileName[] = { "","","" };	//モデル名を入れる配列

	for (int e = 0; e < TYPE_MAX; e++)
	{
		hModel_[e] = Model::Load(fileName[e]);
		assert(hModel_[e] >= 0);
	}

}
*/

