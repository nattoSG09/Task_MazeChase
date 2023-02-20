#include "Timer.h"

const int FPS = 60;

// コンストラクタ
Timer::Timer(GameObject * parent)
	: GameObject(parent, "Timer"), State_(0),Frame_(0),Active_(false),DrawX_(0), DrawY_(0)
{
	//テキストのロード
	pText = new Text;
	pText->Initialize();
}

//デストラクタ
Timer::~Timer()
{
	delete pText;
}

//初期化
void Timer::Initialize()
{
	Frame_ = 0;
	State_ = 0;
	Active_ = false;
}

//更新
void Timer::Update()
{
	switch (State_)
	{
	case TIMER:		TimerUpdate();		break;
	case STOPWATCH: StopWatchUpdate();	break;
	}
}

//更新：Timer
void Timer::TimerUpdate()
{
	if (Active_)//アクティブ時のみカウントを動かす
		if (Frame_ > 0)
		{
			Frame_--;
		}
}

//更新：StopWatch
void Timer::StopWatchUpdate()
{
	if (Active_)//アクティブ時のみカウントを動かす
		Frame_++;
}

//描画
void Timer::Draw()
{
	pText->Draw(DrawX_, DrawY_, "Time:");
	int Sec = Frame_ / FPS;
	pText->Draw(DrawX_+90, DrawY_, Sec);
}

//開放
void Timer::Release()
{
}

//使用する機能を変更する関数
//引数：_state　(Timer::TIMER) / (Timer::STOPWATCH)
void Timer::UseThis(int _state)
{
	State_ = _state;
}

//制限時間を決める関数
void Timer::SetLimit(float seconds_)
{
	Frame_ = (int)(seconds_ * FPS);
}

//カウントを開始する関数
void Timer::TimeStart()
{
	Active_ = true;
}

//カウントを終了する関数
void Timer::TimeStop()
{
	Active_ = false;
}

//終了したかを知らせる関数
bool Timer::IsFinished()
{
	return(Frame_ == 0);
}

//中断したかを知らせる関数
bool Timer::IsStopped()
{
	return(Active_ == false);
}

//使用を考えている関数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ストップウォッチを使用する関数
//void Timer::UseaStopWatch()
//{
//	State_ = STOPWATCH;
//}
//
////タイマーを使用する関数
//void Timer::UseaTimer()
//{
//	State_ = TIMER;
//}
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
