#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//コンストラクタ
Player::Player(GameObject* parent)
{
}
//初期化
void Player::Initialize()
{
}
//更新
void Player::Update()
{
}
//描画
void Player::Draw()
{
}
//開放
void Player::Release()
{
}


/*
//コンストラクタ
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1), pStage_(nullptr)
{
}

//初期化
void Player::Initialize()
{
	hModel_ = Model::Load("F_Enemy(move).fbx");
	assert(hModel_ >= 0);

	transform_.position_.x = 7.0f;
	transform_.position_.z = 7.0f;

	pStage_ = (Stage*)FindObject("Stage");
}

//更新
void Player::Update()
{
	prevPosition_ = transform_.position_;

	XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);	//速度用の行列(※ここでは初期化しただけ)
	if (Input::IsKey(DIK_W))
	{
		//上移動
		fMove.z = Speed_;
		//transform_.rotate_.y = 0.0f;
	}
	if (Input::IsKey(DIK_S))
	{
		//下移動
		fMove.z = -Speed_;
		//transform_.rotate_.y = 180.0f;
	}
	if (Input::IsKey(DIK_A))
	{
		//左移動
		fMove.x = -Speed_;
		//transform_.rotate_.y = 270.0f;
	}
	if (Input::IsKey(DIK_D))
	{
		//右移動
		fMove.x = Speed_;
		//transform_.rotate_.y = 90.0f;
	}

	//=====この一連の処理でどの方向でも等速になる=====
XMVECTOR vMove;
vMove = XMLoadFloat3(&fMove);
vMove = XMVector3Normalize(vMove);
vMove *= Speed_;
XMStoreFloat3(&fMove, vMove);

transform_.position_.x += fMove.x;
transform_.position_.z += fMove.z;
//================================================

//内積で角度出してRotateに入れる
//==================向き変更======================
XMVECTOR vLength = XMVector3Length(vMove);//ベクトルAの長さを求める関数
float length = XMVectorGetX(vLength);	  //上をfloat型に

if (length != 0) {			//vMoveの長さが0じゃない = 動いてないときという条件
	XMVECTOR vFront = { 0,0,1,0 };		//プレイヤーが初期で向いてる奥方向に1の長さを持つベクトルA
	vMove = XMVector3Normalize(vMove);	//今移動してる方向へのベクトルBを正規化

	XMVECTOR vDot = XMVector3Dot(vFront, vMove);//内積を求める ※この関数はなぜかベクトルで返してくる
	float dot = XMVectorGetX(vDot);		//ここでfloat型に変換
	float angle = acos(dot);			//ラジアン角で返されるのには注意

	XMVECTOR vCross = XMVector3Cross(vFront, vMove);	//外積のやつ、クロスは“A × B”とそのまんま
	if (XMVectorGetY(vCross) < 0) {		//外積のY座標がマイナス(左側)なら
		angle *= -1;					//角度をマイナスに修正
	}

	transform_.rotate_.y = XMConvertToDegrees(angle);	//ラジアンを度数に戻すやつ
}
//================================================

//==================壁との判定====================
int checkX1, checkX2;
int checkZ1, checkZ2;

//座標は小数点が入るからそれをintに直しとく
//右-----------------------------------------
{
	//座標の小数点以下を切り捨てて0.3(半径)を足すか引けばめり込みを解決できる

	//この+0.3f(自機の半径)でちゃんと止まるようになる
	checkX1 = (int)(transform_.position_.x + 0.3f);	//transform～の式を()で囲むと型変換の前に計算	
	checkX2 = (int)(transform_.position_.x + 0.3f);	//斜め方向とか
	checkZ1 = (int)(transform_.position_.z + 0.1f);
	checkZ2 = (int)(transform_.position_.z - 0.1f);	//斜め方向
	if (pStage_->IsWall(checkX1, checkZ1) == true ||
		pStage_->IsWall(checkX2, checkZ2) == true) {
		//Debug::Log("めり込んだ！",true);		//壁判定のデバッグ
		//当たる前に戻す
		transform_.position_.x = (float)((int)prevPosition_.x) + (1.0f - 0.3f);	// 0.7

	}
}
//-------------------------------------------
//左-----------------------------------------
{
	checkX1 = (int)(transform_.position_.x - 0.3f);
	checkX2 = (int)(transform_.position_.x - 0.3f);	//斜め方向とか
	checkZ1 = (int)(transform_.position_.z + 0.1f);
	checkZ2 = (int)(transform_.position_.z - 0.1f);	//斜め方向
	if (pStage_->IsWall(checkX1, checkZ1) == true ||
		pStage_->IsWall(checkX2, checkZ2) == true) {
		//Debug::Log("めり込んだ！",true);		//壁判定のデバッグ
		//当たる前に戻す
		transform_.position_.x = (float)((int)prevPosition_.x) + 0.3f;	//小数以下切り捨て→
																		//0.3(自機半径)を足す
	}
}
//-------------------------------------------
//前-----------------------------------------
{
	checkX1 = (int)(transform_.position_.x + 0.1f);
	checkX2 = (int)(transform_.position_.x - 0.1f);	//斜め方向とか
	checkZ1 = (int)(transform_.position_.z + 0.3f);
	checkZ2 = (int)(transform_.position_.z + 0.3f);	//斜め方向
	if (pStage_->IsWall(checkX1, checkZ1) == true ||
		pStage_->IsWall(checkX2, checkZ2) == true) {
		//Debug::Log("めり込んだ！",true);		//壁判定のデバッグ
		//当たる前に戻す
		transform_.position_.z = (float)((int)prevPosition_.z) + (1.0f - 0.3f);	// 0.7

	}
}
//-------------------------------------------
//後-----------------------------------------
{
	checkX1 = (int)(transform_.position_.x + 0.1f);	//手前の
	checkX2 = (int)(transform_.position_.x - 0.1f);
	checkZ1 = (int)(transform_.position_.z - 0.3f);
	checkZ2 = (int)(transform_.position_.z - 0.3f);
	if (pStage_->IsWall(checkX1, checkZ1) == true ||
		pStage_->IsWall(checkX2, checkZ2) == true) {
		//Debug::Log("めり込んだ！",true);		//壁判定のデバッグ
		//当たる前に戻す
		transform_.position_.z = (float)((int)prevPosition_.z) + 0.3f;	//小数以下切り捨て→
																		//0.3(自機半径)を足す

	}
}
//-------------------------------------------
/*================================================*

}

//描画
void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}
*/
