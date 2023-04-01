#include "Player.h"
#include "Engine/SceneManager.h"
#include"Engine/SphereCollider.h"


//�R���X�g���N�^

Player::Player(GameObject* parent)
	: GameObject(parent, "Player"),PlayerTrans_(transform_),hModel_(0),CamType_(0),pStageMap_(nullptr)
	, prevPosition_(0, 0, 0), CamPosition_(0, 0, 0), CamTarget_(0, 0, 0), vPosition_{0,0,0,0}, vMoveZ_{ 0,0,0,0 }, vMoveX_{ 0,0,0,0 }
{
}

//������
void Player::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("F_Player(move).fbx");
	assert(hModel_ >= 0);


	//player�����ݒ�
	{
		PlayerTrans_.position_ = { 3.0f,0.0f,3.0f };//�}�b�v�̍����[
	//�A�j���[�V�������쏈��
		Model::SetAnimFrame(hModel_, 0, 60, 1);
	}
	
	//stage���̎擾
	pStageMap_ = (StageMap*)FindObject("StageMap");

	SphereCollider* collision = new SphereCollider(PlayerTrans_.position_, 1.2f);
	AddCollider(collision);

}
//�X�V
void Player::Update()
{
	
	//player�̓��쏈��
	{
		//�}�E�X�ɂ������擾
		XMFLOAT3 MouseMove_ = Input::GetMouseMove();
		PlayerTrans_.rotate_.y += (MouseMove_.x / 10.0f);


		//�x�N�g����p��
		vPosition_ = XMLoadFloat3(&PlayerTrans_.position_);

		float Speed = 0.05f;

		if (Input::IsKey(DIK_LSHIFT)) {
			Speed = 0.09;
		}

		vMoveZ_ = { 0.0f,0.0f,Speed,0.0f };
		vMoveX_ = { Speed,0.0f,0.0f,0.0f };


		XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(PlayerTrans_.rotate_.y));

		// vMoveZ / vMoveX ��RotateMatY�ŉ�]������
		vMoveZ_ = XMVector3TransformCoord(vMoveZ_, RotateMatY);
		vMoveX_ = XMVector3TransformCoord(vMoveX_, RotateMatY);

		//�uW�v�L�[�F�O�ɐi��
		if (Input::IsKey(DIK_W)) {
			vPosition_ += vMoveZ_;
			XMVector3Normalize(vMoveZ_);//�ړ��x�N�g���𐳋K��
		}

		//�uS�v�L�[�F���ɐi��
		if (Input::IsKey(DIK_S)) {
			vPosition_ -= vMoveZ_;
			XMVector3Normalize(vMoveZ_);//�ړ��x�N�g���𐳋K��
		}

		//�uA�v�L�[�F���ɐi��
		if (Input::IsKey(DIK_A)) {
			vPosition_ -= vMoveX_;
			XMVector3Normalize(vMoveX_);//�ړ��x�N�g���𐳋K��
		}

		//�uD�v�L�[�F�E�ɐi��
		if (Input::IsKey(DIK_D)) {
			vPosition_ += vMoveX_;
			XMVector3Normalize(vMoveX_);//�ړ��x�N�g���𐳋K��
		}


		XMVector3Normalize(vPosition_);//�ړ��x�N�g���𐳋K��
		XMStoreFloat3(&PlayerTrans_.position_, vPosition_);
	}
	
	//�J�����̕ύX����
	{
		//�J������ύX����
		if (Input::IsKeyDown(DIK_F4)) { CamChange(); }

		switch (CamType_)
		{
		case CAM_FIXED:	CamSet_FIXED();	break;
		case CAM_FPS:	CamSet_FPS();	break;
		}

		Camera::SetPosition(CamPosition_);
		Camera::SetTarget(CamTarget_);
	}

	//�f�o�b�N�p�F�����蔻��m�F
	#if 0
	{
		//Player���ǂƐڐG���Ă��邩���m�F����
		if (pStageMap_->IsWall(PlayerTrans_.position_.x, PlayerTrans_.position_.z)) {
			Debug::Log("�Z", true);
		}
		else {
			Debug::Log("��", true);
		}
	}
	#endif

	//�����蔻��̏���
	boundaryCheck();
}

//�`��
void Player::Draw()
{
	Model::SetTransform(hModel_, PlayerTrans_);
	Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}

//���_��ύX����֐�
void Player::CamChange()
{
	if (CamType_ < (CAM_MAX - 1))
		CamType_++;
	else
		CamType_ = 0;
}

//���_��ݒ肷��֐��F��l��
void Player::CamSet_FPS()
{
	//�J�����̈ʒu��player�̈ʒu�ɃZ�b�g
	XMVECTOR FPup = { 0.0f,1.2f,0.0f };
	XMStoreFloat3(&CamPosition_, vPosition_ + FPup);
	//�J�����̏œ_��player�̖ڐ�ɃZ�b�g
	XMStoreFloat3(&CamTarget_, vPosition_ + vMoveZ_ + FPup);
}

//���_��ݒ肷��֐��F�Œ�ʒu����̒Ǐ]
void Player::CamSet_FIXED()
{
	//CamTarget_ = { PlayerTrans_.position_ };
	CamTarget_ = { 15,5,15 };
	CamPosition_ = { 15,50,14};
}

//�ǂƂ̂����蔻�菈��
void Player::boundaryCheck()
{
	//�����蔻��̊e���_���\��
	int checkX1, checkX2;
	int checkZ1, checkZ2;
	//���W�͏����_�����邩�炻���int�ɒ����Ƃ�
//�E-----------------------------------------
	{
		//���_�P
		checkX1 = (int)(PlayerTrans_.position_.x + 0.2f);
		checkZ1 = (int)(PlayerTrans_.position_.z + 0.1f);
		//���_�Q
		checkX2 = (int)(PlayerTrans_.position_.x + 0.2f);
		checkZ2 = (int)(PlayerTrans_.position_.z - 0.1f);

		//�Փ˂��Ă��邩�ǂ���
		if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
		{
			PlayerTrans_.position_.x = (float)((int)PlayerTrans_.position_.x) + (1.0f - 0.2f);
		}
	}
	//-------------------------------------------
	//���W�͏����_�����邩�炻���int�ɒ����Ƃ�
	//��-----------------------------------------
	{
		//���_�P
		checkX1 = (int)(PlayerTrans_.position_.x - 0.2f);
		checkZ1 = (int)(PlayerTrans_.position_.z + 0.1f);
		//���_�Q
		checkX2 = (int)(PlayerTrans_.position_.x - 0.2f);
		checkZ2 = (int)(PlayerTrans_.position_.z - 0.1f);

		//�Փ˂��Ă��邩�ǂ���
		if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
		{
			PlayerTrans_.position_.x = (float)((int)PlayerTrans_.position_.x) + 0.2f;
		}
	}
	//-------------------------------------------
	//���W�͏����_�����邩�炻���int�ɒ����Ƃ�
	//��-----------------------------------------
	{
		//���_�P
		checkX1 = (int)(PlayerTrans_.position_.x + 0.1f);
		checkZ1 = (int)(PlayerTrans_.position_.z + 0.2f);
		//���_�Q
		checkX2 = (int)(PlayerTrans_.position_.x - 0.1f);
		checkZ2 = (int)(PlayerTrans_.position_.z + 0.2f);

		//�Փ˂��Ă��邩�ǂ���
		if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
		{
			PlayerTrans_.position_.z = (float)((int)PlayerTrans_.position_.z) + (1.0f - 0.2f);
		}
	}
	//-------------------------------------------
	//���W�͏����_�����邩�炻���int�ɒ����Ƃ�
	//��-----------------------------------------
	{
		//���_�P
		checkX1 = (int)(PlayerTrans_.position_.x + 0.1f);
		checkZ1 = (int)(PlayerTrans_.position_.z - 0.2f);
		//���_�Q
		checkX2 = (int)(PlayerTrans_.position_.x - 0.1f);
		checkZ2 = (int)(PlayerTrans_.position_.z - 0.2f);
		if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
		{
			PlayerTrans_.position_.z = (float)((int)PlayerTrans_.position_.z) + 0.2f;
		}
	}
	//-------------------------------------------
}

////�C�ӂ̃Q�[���I�u�W�F�N�g�Ɂu�����[�g����łԂ��邩�v�����߂�֐�
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