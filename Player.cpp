#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"

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
	hModel_ = Model::Load("F_Enemy(move).fbx");
	assert(hModel_ >= 0);

	//�����ʒu�̐ݒ�
	PlayerTrans_.position_ = { 3,1,3 };//�}�b�v�̍����[

	//�A�j���[�V�������쏈��
	Model::SetAnimFrame(hModel_, 0, 60, 1);


	pStageMap_ = (StageMap*)FindObject("StageMap");
}
//�X�V
void Player::Update()
{
//������������������������������������������������������������������������������
//  �L�����N�^�[�̈ړ�����
//������������������������������������������������������������������������������

	//�}�E�X�ɂ������擾
	XMFLOAT3 MouseMove_ = Input::GetMouseMove();
	PlayerTrans_.rotate_.y += (MouseMove_.x / 10.0f);


	//�x�N�g����p��
	vPosition_ = XMLoadFloat3(&PlayerTrans_.position_);

	float Speed = 0.1f;
	vMoveZ_ = { 0.0f,0.0f,Speed,0.0f };
	vMoveX_ = { Speed,0.0f,0.0f,0.0f };

	XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(PlayerTrans_.rotate_.y));

	// vMoveZ / vMoveX ��RotateMatY�ŉ�]������
	vMoveZ_ = XMVector3TransformCoord(vMoveZ_, RotateMatY);
	vMoveX_ = XMVector3TransformCoord(vMoveX_, RotateMatY);

	//�uW�v�L�[�F�O�ɐi��
	if (Input::IsKey(DIK_W)) {
		vPosition_ += vMoveZ_;
		XMStoreFloat3(&PlayerTrans_.position_, vPosition_);
	}

	//�uS�v�L�[�F���ɐi��
	if (Input::IsKey(DIK_S)) {
		vPosition_ -= vMoveZ_;
		XMStoreFloat3(&PlayerTrans_.position_, vPosition_);
	}

	//�uA�v�L�[�F���ɐi��
	if (Input::IsKey(DIK_A)) {
		vPosition_ -= vMoveX_;
		XMStoreFloat3(&PlayerTrans_.position_, vPosition_);
	}

	//�uD�v�L�[�F�E�ɐi��
	if (Input::IsKey(DIK_D)) {
		vPosition_ += vMoveX_;
		XMStoreFloat3(&PlayerTrans_.position_, vPosition_);
	}

//������������������������������������������������������������������������������
//  �J�����̈ړ�����
//������������������������������������������������������������������������������

	//�J������ύX����
	if (Input::IsKeyDown(DIK_F4)) { CamChange(); }

	switch (CamType_)
	{
	case CAM_FIXED:	CamSet_FIXED();	break;
	case CAM_FPS:	CamSet_FPS();	break;
	}

	Camera::SetPosition(CamPosition_);
	Camera::SetTarget(CamTarget_);


/*==================�ǂƂ̔���====================*/
int checkX1, checkX2;
int checkZ1, checkZ2;


	//�f�o�b�N�p
	//Player���ǂƐڐG���Ă��邩���m�F����
	if (pStageMap_->IsWall(PlayerTrans_.position_.x, PlayerTrans_.position_.z)) {
		Debug::Log("�Z", true);
	}
	else {
		Debug::Log("��", true);
	}

	//���W�͏����_�����邩�炻���int�ɒ����Ƃ�
	//�E-----------------------------------------
	{

		checkX1 = (int)(transform_.position_.x + 1.0f);	
		checkX2 = (int)(transform_.position_.x + 1.0f);	
		checkZ1 = (int)(transform_.position_.z + 0.3f);
		checkZ2 = (int)(transform_.position_.z - 0.3f);	
		if (pStageMap_->IsWall(checkX1, checkZ1) == true ||
			pStageMap_->IsWall(checkX2, checkZ2) == true) {
			Debug::Log("�߂荞�񂾁I",true);		//�ǔ���̃f�o�b�O
			//������O�ɖ߂�
			//transform_.position_.x = (float)((int)prevPosition_.x) + (1.0f - 0.3f);	// 0.7

		}
	}
	//-------------------------------------------
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
	XMVECTOR FPup = { 0.0f,0.5f,0.0f };
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



/*
//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1), pStage_(nullptr)
{
}

//������
void Player::Initialize()
{
	hModel_ = Model::Load("F_Enemy(move).fbx");
	assert(hModel_ >= 0);

	transform_.position_.x = 7.0f;
	transform_.position_.z = 7.0f;

	pStage_ = (Stage*)FindObject("Stage");
}

//�X�V
void Player::Update()
{
	prevPosition_ = transform_.position_;

	XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);	//���x�p�̍s��(�������ł͏�������������)
	if (Input::IsKey(DIK_W))
	{
		//��ړ�
		fMove.z = Speed_;
		//transform_.rotate_.y = 0.0f;
	}
	if (Input::IsKey(DIK_S))
	{
		//���ړ�
		fMove.z = -Speed_;
		//transform_.rotate_.y = 180.0f;
	}
	if (Input::IsKey(DIK_A))
	{
		//���ړ�
		fMove.x = -Speed_;
		//transform_.rotate_.y = 270.0f;
	}
	if (Input::IsKey(DIK_D))
	{
		//�E�ړ�
		fMove.x = Speed_;
		//transform_.rotate_.y = 90.0f;
	}

	//=====���̈�A�̏����łǂ̕����ł������ɂȂ�=====
XMVECTOR vMove;
vMove = XMLoadFloat3(&fMove);
vMove = XMVector3Normalize(vMove);
vMove *= Speed_;
XMStoreFloat3(&fMove, vMove);

transform_.position_.x += fMove.x;
transform_.position_.z += fMove.z;
//================================================

//���ςŊp�x�o����Rotate�ɓ����
//==================�����ύX======================
XMVECTOR vLength = XMVector3Length(vMove);//�x�N�g��A�̒��������߂�֐�
float length = XMVectorGetX(vLength);	  //���float�^��

if (length != 0) {			//vMove�̒�����0����Ȃ� = �����ĂȂ��Ƃ��Ƃ�������
	XMVECTOR vFront = { 0,0,1,0 };		//�v���C���[�������Ō����Ă鉜������1�̒��������x�N�g��A
	vMove = XMVector3Normalize(vMove);	//���ړ����Ă�����ւ̃x�N�g��B�𐳋K��

	XMVECTOR vDot = XMVector3Dot(vFront, vMove);//���ς����߂� �����̊֐��͂Ȃ����x�N�g���ŕԂ��Ă���
	float dot = XMVectorGetX(vDot);		//������float�^�ɕϊ�
	float angle = acos(dot);			//���W�A���p�ŕԂ����̂ɂ͒���

	XMVECTOR vCross = XMVector3Cross(vFront, vMove);	//�O�ς̂�A�N���X�́gA �~ B�h�Ƃ��̂܂��
	if (XMVectorGetY(vCross) < 0) {		//�O�ς�Y���W���}�C�i�X(����)�Ȃ�
		angle *= -1;					//�p�x���}�C�i�X�ɏC��
	}

	transform_.rotate_.y = XMConvertToDegrees(angle);	//���W�A����x���ɖ߂����
}
//================================================

//==================�ǂƂ̔���====================
int checkX1, checkX2;
int checkZ1, checkZ2;

//���W�͏����_�����邩�炻���int�ɒ����Ƃ�
//�E-----------------------------------------
{
	//���W�̏����_�ȉ���؂�̂Ă�0.3(���a)�𑫂��������΂߂荞�݂������ł���

	//����+0.3f(���@�̔��a)�ł����Ǝ~�܂�悤�ɂȂ�
	checkX1 = (int)(transform_.position_.x + 0.3f);	//transform�`�̎���()�ň͂ނƌ^�ϊ��̑O�Ɍv�Z	
	checkX2 = (int)(transform_.position_.x + 0.3f);	//�΂ߕ����Ƃ�
	checkZ1 = (int)(transform_.position_.z + 0.1f);
	checkZ2 = (int)(transform_.position_.z - 0.1f);	//�΂ߕ���
	if (pStage_->IsWall(checkX1, checkZ1) == true ||
		pStage_->IsWall(checkX2, checkZ2) == true) {
		//Debug::Log("�߂荞�񂾁I",true);		//�ǔ���̃f�o�b�O
		//������O�ɖ߂�
		transform_.position_.x = (float)((int)prevPosition_.x) + (1.0f - 0.3f);	// 0.7

	}
}
//-------------------------------------------
//��-----------------------------------------
{
	checkX1 = (int)(transform_.position_.x - 0.3f);
	checkX2 = (int)(transform_.position_.x - 0.3f);	//�΂ߕ����Ƃ�
	checkZ1 = (int)(transform_.position_.z + 0.1f);
	checkZ2 = (int)(transform_.position_.z - 0.1f);	//�΂ߕ���
	if (pStage_->IsWall(checkX1, checkZ1) == true ||
		pStage_->IsWall(checkX2, checkZ2) == true) {
		//Debug::Log("�߂荞�񂾁I",true);		//�ǔ���̃f�o�b�O
		//������O�ɖ߂�
		transform_.position_.x = (float)((int)prevPosition_.x) + 0.3f;	//�����ȉ��؂�̂ā�
																		//0.3(���@���a)�𑫂�
	}
}
//-------------------------------------------
//�O-----------------------------------------
{
	checkX1 = (int)(transform_.position_.x + 0.1f);
	checkX2 = (int)(transform_.position_.x - 0.1f);	//�΂ߕ����Ƃ�
	checkZ1 = (int)(transform_.position_.z + 0.3f);
	checkZ2 = (int)(transform_.position_.z + 0.3f);	//�΂ߕ���
	if (pStage_->IsWall(checkX1, checkZ1) == true ||
		pStage_->IsWall(checkX2, checkZ2) == true) {
		//Debug::Log("�߂荞�񂾁I",true);		//�ǔ���̃f�o�b�O
		//������O�ɖ߂�
		transform_.position_.z = (float)((int)prevPosition_.z) + (1.0f - 0.3f);	// 0.7

	}
}
//-------------------------------------------
//��-----------------------------------------
{
	checkX1 = (int)(transform_.position_.x + 0.1f);	//��O��
	checkX2 = (int)(transform_.position_.x - 0.1f);
	checkZ1 = (int)(transform_.position_.z - 0.3f);
	checkZ2 = (int)(transform_.position_.z - 0.3f);
	if (pStage_->IsWall(checkX1, checkZ1) == true ||
		pStage_->IsWall(checkX2, checkZ2) == true) {
		//Debug::Log("�߂荞�񂾁I",true);		//�ǔ���̃f�o�b�O
		//������O�ɖ߂�
		transform_.position_.z = (float)((int)prevPosition_.z) + 0.3f;	//�����ȉ��؂�̂ā�
																		//0.3(���@���a)�𑫂�

	}
}
//-------------------------------------------
/*================================================*

}

//�`��
void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}
*/
