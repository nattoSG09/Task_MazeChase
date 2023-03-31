#pragma once
#include <vector>
using std::vector;

#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"
#include "Engine/Model.h"

#include "StageObject.h"


class StageMap : public GameObject
{
private:
	enum
	{
		TYPE_FLOOR,
		TYPE_WALL,
		TYPE_MAX
	};

	CsvReader CsvMap_;	
	int hModel_[TYPE_MAX];
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

	// 指定した位置が通れるか通れないかを調べる
	//引数：x,z	調べる位置
	//戻り値：壁＝true / 壁じゃない＝false
	bool IsWall(int x, int z);

	//table.size & dataを他所に渡す関数
	vector<vector<int>>& GetTable_() { return(this->table_); }

	//table.Widthを渡す関数
	int GetWidth() { return (this->Width); }

	//table.Heightを渡す関数
	int GetHeight() { return (this->Height); }

	//プレゼンハムのアルゴリズム関数
	bool HasWallBetween(XMFLOAT3 _positionA, XMFLOAT3 _positionB);
};