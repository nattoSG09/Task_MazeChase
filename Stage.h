#pragma once
#include "Engine/GameObject.h"

enum
{
	TYPE_FLOOR,
	TYPE_WALL,
	TYPE_MAX
};

class Stage :
	public GameObject
{
	//配列で複数扱うほうが良い！
	int hModel_[TYPE_MAX];	//[]内をenumに書いたMAXにすることで、配列数をいじることもない
	int** table_;		//フロアの座標
	int width_, height_;			//フロアのx,z座標


public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Stage(GameObject* parent);

	//デストラクタ
	~Stage();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//変数"table"のゲッター
	//int GetTable() { return **table_; }	//←これだとポインタ全体の情報を持ってくる

	//指定した位置が通れるか通れないかを調べる
	//引数：x,z	調べる位置
	//戻り値：通れない＝true / 通れない＝false
	bool IsWall(int x, int z);
};