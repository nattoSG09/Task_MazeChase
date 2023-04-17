#include "StageMap.h"

//コンストラクタ
StageMap::StageMap(GameObject* parent)
	: GameObject(parent, "StageMap"),hModel_{},Width(0),Height(0),table_{}
{
	//CSVデータのロード
	{
		CsvMap_.Load("M_Map2.csv");

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
bool StageMap::HasWallBetween(XMFLOAT3 _posA, XMFLOAT3 _posB)
{
	//プレイヤーの位置と敵の位置の間の距離を求める
	float distance = sqrt(pow(_posB.x - _posA.x, 2) + pow(_posB.z - _posA.z, 2));

	//2点間を等分する点を作る
	float dx = (_posB.x - _posA.x) / distance;
	float dz = (_posB.z - _posA.z) / distance;
	float x = _posA.x;
	float z = _posA.z;

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
