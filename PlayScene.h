#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Transition.h"
#include "MiniMap.h"
#include "StageMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"
#include "Coin.h"


class PlayScene : public GameObject
{
public:
	enum {
		STATE_READY,
		STATE_PLAY,
		STATE_FINISH,
	};
	int state_;
private:
	Timer* Time_;
	MiniMap* MiniMap_;
	Transition* transition_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//更新・準備
	void UpdateReady();

	//更新・プレイ中
	void UpdatePlay();
	
	//更新・終了
	void UpdateFinish();

	//描画
	void Draw() override;

	//開放
	void Release() override;
};