#include "Player.h"
#include "Engine/SceneManager.h"
#include"Engine/SphereCollider.h"


//コンストラクタ

Player::Player(GameObject* parent)
	: GameObject(parent, "Player"),PlayerTrans_(transform_),hModel_(0),CamType_(0),pStageMap_(nullptr)
	, prevPosition_(0, 0, 0), CamPosition_(0, 0, 0), CamTarget_(0, 0, 0), vPosition_{0,0,0,0}, vMoveZ_{ 0,0,0,0 }, vMoveX_{ 0,0,0,0 }
{
}

//初期化
void Player::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("F_Player(move).fbx");
	assert(hModel_ >= 0);


	//player初期設定
	{
		PlayerTrans_.position_ = { 3.0f,0.0f,3.0f };//マップの左下端
	//アニメーション動作処理
		Model::SetAnimFrame(hModel_, 0, 60, 1);
	}
	
	//stage情報の取得
	pStageMap_ = (StageMap*)FindObject("StageMap");

	SphereCollider* collision = new SphereCollider(PlayerTrans_.position_, 1.2f);
	AddCollider(collision);

}
//更新
void Player::Update()
{
	
	//playerの動作処理
	{
		//マウスによる方向取得
		XMFLOAT3 MouseMove_ = Input::GetMouseMove();
		PlayerTrans_.rotate_.y += (MouseMove_.x / 10.0f);


		//ベクトルを用意
		vPosition_ = XMLoadFloat3(&PlayerTrans_.position_);

		float Speed = 0.05f;

		if (Input::IsKey(DIK_LSHIFT)) {
			Speed = 0.09;
		}

		vMoveZ_ = { 0.0f,0.0f,Speed,0.0f };
		vMoveX_ = { Speed,0.0f,0.0f,0.0f };


		XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(PlayerTrans_.rotate_.y));

		// vMoveZ / vMoveX をRotateMatYで回転させる
		vMoveZ_ = XMVector3TransformCoord(vMoveZ_, RotateMatY);
		vMoveX_ = XMVector3TransformCoord(vMoveX_, RotateMatY);

		//「W」キー：前に進む
		if (Input::IsKey(DIK_W)) {
			vPosition_ += vMoveZ_;
			XMVector3Normalize(vMoveZ_);//移動ベクトルを正規化
		}

		//「S」キー：後ろに進む
		if (Input::IsKey(DIK_S)) {
			vPosition_ -= vMoveZ_;
			XMVector3Normalize(vMoveZ_);//移動ベクトルを正規化
		}

		//「A」キー：左に進む
		if (Input::IsKey(DIK_A)) {
			vPosition_ -= vMoveX_;
			XMVector3Normalize(vMoveX_);//移動ベクトルを正規化
		}

		//「D」キー：右に進む
		if (Input::IsKey(DIK_D)) {
			vPosition_ += vMoveX_;
			XMVector3Normalize(vMoveX_);//移動ベクトルを正規化
		}


		XMVector3Normalize(vPosition_);//移動ベクトルを正規化
		XMStoreFloat3(&PlayerTrans_.position_, vPosition_);
	}
	
	//カメラの変更処理
	{
		//カメラを変更する
		if (Input::IsKeyDown(DIK_F4)) { CamChange(); }

		switch (CamType_)
		{
		case CAM_FIXED:	CamSet_FIXED();	break;
		case CAM_FPS:	CamSet_FPS();	break;
		}

		Camera::SetPosition(CamPosition_);
		Camera::SetTarget(CamTarget_);
	}

	//デバック用：あたり判定確認
	#if 0
	{
		//Playerが壁と接触しているかを確認する
		if (pStageMap_->IsWall(PlayerTrans_.position_.x, PlayerTrans_.position_.z)) {
			Debug::Log("〇", true);
		}
		else {
			Debug::Log("△", true);
		}
	}
	#endif

	//あたり判定の処理
	boundaryCheck();
}

//描画
void Player::Draw()
{
	Model::SetTransform(hModel_, PlayerTrans_);
	Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}

//視点を変更する関数
void Player::CamChange()
{
	if (CamType_ < (CAM_MAX - 1))
		CamType_++;
	else
		CamType_ = 0;
}

//視点を設定する関数：一人称
void Player::CamSet_FPS()
{
	//カメラの位置をplayerの位置にセット
	XMVECTOR FPup = { 0.0f,1.2f,0.0f };
	XMStoreFloat3(&CamPosition_, vPosition_ + FPup);
	//カメラの焦点をplayerの目先にセット
	XMStoreFloat3(&CamTarget_, vPosition_ + vMoveZ_ + FPup);
}

//視点を設定する関数：固定位置からの追従
void Player::CamSet_FIXED()
{
	//CamTarget_ = { PlayerTrans_.position_ };
	CamTarget_ = { 15,5,15 };
	CamPosition_ = { 15,50,14};
}

//壁とのあたり判定処理
void Player::boundaryCheck()
{
	//あたり判定の各頂点を構成
	int checkX1, checkX2;
	int checkZ1, checkZ2;
	//座標は小数点が入るからそれをintに直しとく
//右-----------------------------------------
	{
		//頂点１
		checkX1 = (int)(PlayerTrans_.position_.x + 0.2f);
		checkZ1 = (int)(PlayerTrans_.position_.z + 0.1f);
		//頂点２
		checkX2 = (int)(PlayerTrans_.position_.x + 0.2f);
		checkZ2 = (int)(PlayerTrans_.position_.z - 0.1f);

		//衝突しているかどうか
		if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
		{
			PlayerTrans_.position_.x = (float)((int)PlayerTrans_.position_.x) + (1.0f - 0.2f);
		}
	}
	//-------------------------------------------
	//座標は小数点が入るからそれをintに直しとく
	//左-----------------------------------------
	{
		//頂点１
		checkX1 = (int)(PlayerTrans_.position_.x - 0.2f);
		checkZ1 = (int)(PlayerTrans_.position_.z + 0.1f);
		//頂点２
		checkX2 = (int)(PlayerTrans_.position_.x - 0.2f);
		checkZ2 = (int)(PlayerTrans_.position_.z - 0.1f);

		//衝突しているかどうか
		if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
		{
			PlayerTrans_.position_.x = (float)((int)PlayerTrans_.position_.x) + 0.2f;
		}
	}
	//-------------------------------------------
	//座標は小数点が入るからそれをintに直しとく
	//上-----------------------------------------
	{
		//頂点１
		checkX1 = (int)(PlayerTrans_.position_.x + 0.1f);
		checkZ1 = (int)(PlayerTrans_.position_.z + 0.2f);
		//頂点２
		checkX2 = (int)(PlayerTrans_.position_.x - 0.1f);
		checkZ2 = (int)(PlayerTrans_.position_.z + 0.2f);

		//衝突しているかどうか
		if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
		{
			PlayerTrans_.position_.z = (float)((int)PlayerTrans_.position_.z) + (1.0f - 0.2f);
		}
	}
	//-------------------------------------------
	//座標は小数点が入るからそれをintに直しとく
	//下-----------------------------------------
	{
		//頂点１
		checkX1 = (int)(PlayerTrans_.position_.x + 0.1f);
		checkZ1 = (int)(PlayerTrans_.position_.z - 0.2f);
		//頂点２
		checkX2 = (int)(PlayerTrans_.position_.x - 0.1f);
		checkZ2 = (int)(PlayerTrans_.position_.z - 0.2f);
		if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
		{
			PlayerTrans_.position_.z = (float)((int)PlayerTrans_.position_.z) + 0.2f;
		}
	}
	//-------------------------------------------
}

////任意のゲームオブジェクトに「何メートル先でぶつかるか」を求める関数
int Player::GetModelHandle()
{
	return (hModel_);
}

void Player::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Enemy") {

		/*SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);*/

	}
}