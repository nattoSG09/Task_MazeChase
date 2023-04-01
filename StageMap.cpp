#include "StageMap.h"






//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝：StageMap.cpp説明：＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//「ステージマップクラス」ここはの詳細を設定するクラス。		
// 
// 
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝=＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

//コンストラクタ
StageMap::StageMap(GameObject* parent)
	: GameObject(parent, "StageMap"),hModel_{-1,-1}
{
	//CSVデータのロード
	{
		CsvMap_.Load("M_Map1.csv");

		Width = CsvMap_.GetWidth();
		Height = CsvMap_.GetHeight();

		//配列をWidth×Heightで初期化
		table_.resize(Width, vector<int>(Height, 0));

		for (int x = 0; x < Width; x++)
			for (int z = 0; z < Height; z++)
				table_[x][z] = CsvMap_.GetValue(x, ((Height - 1) - z));
	}
	
}

//初期化
void StageMap::Initialize()
{
	//objectの配置
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
	
}

bool StageMap::IsWall(int x, int z)
{
	return(table_[x/2][z/2] == OBJ_WALL);
}

//プレゼンハムのアルゴリズム関数
bool StageMap::HasWallBetween(XMFLOAT3 _positionA, XMFLOAT3 _positionB)
{
	//プレイヤーの位置と敵の位置の間の距離を求める
	float distance = sqrt(pow(_positionB.x - _positionA.x, 2) + pow(_positionB.z - _positionA.z, 2));

	//2点間を等分する点を作る
	float dx = (_positionB.x - _positionA.x) / distance;
	float dz = (_positionB.z - _positionA.z) / distance;
	float x = _positionA.x;
	float z = _positionA.z;

	//2点間を区切る数だけループ
	const int numPoints = (int)distance;

	// 結果をチェック
	bool hasWall = false;

	for (int i = 0; i < numPoints; i++)
	{
		//プレイヤーと敵の間に壁があるかどうかを判定
		if (IsWall((int)(x), (int)(z)))
		{
			hasWall = true;
		}

		//次の点へ進む
		x += dx;
		z += dz;
	}

	//壁がない場合はfalseを返す
	return hasWall;
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

