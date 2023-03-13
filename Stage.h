#pragma once
#include "Engine/GameObject.h"



class Stage :
	public GameObject
{
private:
	

	//配列で複数扱うほうが良い！

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

};

