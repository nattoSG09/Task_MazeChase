#include "Enemy.h"
#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"),hModel_(-1), Speed_(0.0f), prevPosition_(0,0,0)
{
}

//初期化
void Enemy::Initialize()
{
	hModel_ = Model::Load("F_Enemy(move).fbx");
	assert(hModel_ >= 0);

	//transform_.position_.x = .0f;
	//transform_.position_.z = .0f;

	//pStage_ = (Stage*)FindObject("Stage");
}

//更新
void Enemy::Update()
{
}

//描画
void Enemy::Draw()
{
}

//開放
void Enemy::Release()
{
}