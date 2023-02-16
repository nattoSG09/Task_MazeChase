#include "StageMap.h"
#include "Stage.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝：StageMap.cpp説明：＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//「ステージマップクラス」ここはの詳細を設定するクラス。		
// 
// 
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝=＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝


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