#pragma once
#include "Engine/GameObject.h"

class StageMap :public GameObject
{
private:
	enum {
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_ITEM,
		TYPE_MAX
	};

	int hModel_[TYPE_MAX];	//モデル番号
	int** table_;			//フロアの座標
	int width_, height_;	//フロアのx,z座標

public:
	StageMap(GameObject* parent);

	~StageMap();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release()override;
};
