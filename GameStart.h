#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Transition.h"

class GameStart : public GameObject
{
private:
	int hPict_;
	int camChange_;
	Transition* transition_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GameStart(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};