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

	int hModel_[TYPE_MAX];	//���f���ԍ�
	int** table_;			//�t���A�̍��W
	int width_, height_;	//�t���A��x,z���W

public:
	StageMap(GameObject* parent);

	~StageMap();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release()override;
};
