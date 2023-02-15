#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class Timer : public GameObject
{
public:
	//ステートパターン
	enum {
		TIMER,
		STOPWATCH,
	};

	int State_;//ステート状態を格納する変数

private:

	int Frame_;//残り時間を数える変数
	
	bool Active_;//trueの時にカウントダウン/アップする
	Text* pText;
	int DrawX_, DrawY_;//表示位置

public:
	//コンストラクタ
	Timer(GameObject* parent);

	//デストラクタ
	~Timer();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//更新：タイマー
	void TimerUpdate();

	//更新：ストップウォッチ
	void StopWatchUpdate();

	//描画
	void Draw() override;

	//開放
	void Release() override;


	//＝＝＝＝＝＝Timer関数＝＝＝＝＝＝

	//使用する機能を変更する関数
	//引数：_state　(Timer::TIMER) or (Timer::STOPWATCH)
	void UseThis(int _state);

	//制限時間を(秒)で設定する関数
	//引数：seconds_(秒)
	void SetLimit(float seconds_);

	//カウントを開始する関数
	void TimeStart();

	//カウントを終了する関数
	void TimeStop();

	//終了したかを知らせる関数
	bool IsFinished();

	//中断したかを知らせる関数
	bool IsStopped();

	//画面の表示位置を指定する関数
	//引数１： _x (X座標)
	//引数２： _y (Y座標)
	void DrawPostion(int _x, int _y) { DrawX_ = _x, DrawY_ = _y; }
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
};

//使用を考えている関数
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	////ストップウォッチを使用する関数
	//void UseaStopWatch();
	////タイマーを使用する関数
	//void UseaTimer();
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

