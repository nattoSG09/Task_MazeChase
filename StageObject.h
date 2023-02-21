#pragma once
#include "Engine/GameObject.h"


enum {
	OBJ_FLOOR,
	OBJ_WALL,
	OBJ_MAX,
};

class StageObject : public GameObject
{
	int hModel_[OBJ_MAX];	//モデル番号
	int obj_;				//オブジェクト番号
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	StageObject(GameObject* parent);

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

	//任意のゲームオブジェクトに「何メートル先でぶつかるか」を求める関数
	int GetModelHandle(int _obj);
};