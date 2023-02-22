#include "Enemy.h"
#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"),hModel_(-1),pStage_(nullptr)
{
}

//������
void Enemy::Initialize()
{
	//hModel_ = Model::Load(".fbx");
	//assert(hModel_ >= 0);

	//transform_.position_.x = .0f;
	//transform_.position_.z = .0f;

	//pStage_ = (Stage*)FindObject("Stage");
}

//�X�V
void Enemy::Update()
{
#if 0
	prevPosition_ = transform_.position_;
	Speed_ = 0.1f;
	XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);	//���x�p�̍s���������

/*========�ǂ̊p�x�ł������ɂȂ鏈��========*/
	XMVECTOR vMove;
	vMove = XMLoadFloat3(&fMove);
	vMove = XMVector3Normalize(vMove);
	vMove *= Speed_;
	XMStoreFloat3(&fMove, vMove);

	transform_.position_.x += fMove.x;
	transform_.position_.z += fMove.z;
/*==========================================*/

/*==================�����ύX======================*/
	XMVECTOR vLength = XMVector3Length(vMove);//�x�N�g��A�̒��������߂�֐�
	float length = XMVectorGetX(vLength);	  //���float�^��

	if (length != 0) {						//vMove�̒�����0����Ȃ� = �����ĂȂ��Ƃ��Ƃ�������
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
	/*================================================*/

	/*==================�ǂƂ̔���====================*/
	int checkX1, checkX2;
	int checkZ1, checkZ2;

	//���W�͏����_�����邩�炻���int�ɒ����Ƃ�
	//�E-----------------------------------------
	{
		//���W�̏����_�ȉ���؂�̂Ă�0.3(���a)�𑫂��������΂߂荞�݂������ł���

		//����+0.3f(���@�̔��a)�ł����Ǝ~�܂�悤�ɂȂ�
		checkX1 = (int)(transform_.position_.x + 0.3f);	//transform�`�̎���()�ň͂ނƌ^�ϊ��̑O�Ɍv�Z	
		checkX2 = (int)(transform_.position_.x + 0.3f);
		checkZ1 = (int)(transform_.position_.z + 0.1f);
		checkZ2 = (int)(transform_.position_.z - 0.1f);
		if (pStage_->IsWall(checkX1, checkZ1) == true ||
			pStage_->IsWall(checkX2, checkZ2) == true) {
			//������O�ɖ߂�
			transform_.position_.x = (float)((int)prevPosition_.x) + (1.0f - 0.3f);	// 0.7

		}
	}
	//-------------------------------------------
	//��-----------------------------------------
	{
		checkX1 = (int)(transform_.position_.x - 0.3f);
		checkX2 = (int)(transform_.position_.x - 0.3f);
		checkZ1 = (int)(transform_.position_.z + 0.1f);
		checkZ2 = (int)(transform_.position_.z - 0.1f);
		if (pStage_->IsWall(checkX1, checkZ1) == true ||
			pStage_->IsWall(checkX2, checkZ2) == true) {
			//������O�ɖ߂�
			transform_.position_.x = (float)((int)prevPosition_.x) + 0.3f;	//�����ȉ��؂�̂ā�
																			//0.3(���@���a)�𑫂�
		}
	}
	//-------------------------------------------
	//�O-----------------------------------------
	{
		checkX1 = (int)(transform_.position_.x + 0.1f);
		checkX2 = (int)(transform_.position_.x - 0.1f);
		checkZ1 = (int)(transform_.position_.z + 0.3f);
		checkZ2 = (int)(transform_.position_.z + 0.3f);
		if (pStage_->IsWall(checkX1, checkZ1) == true ||
			pStage_->IsWall(checkX2, checkZ2) == true) {
			//������O�ɖ߂�
			transform_.position_.z = (float)((int)prevPosition_.z) + (1.0f - 0.3f);	// 0.7

		}
	}
	//-------------------------------------------
	//��-----------------------------------------
	{
		checkX1 = (int)(transform_.position_.x + 0.1f);	
		checkX2 = (int)(transform_.position_.x - 0.1f);
		checkZ1 = (int)(transform_.position_.z - 0.3f);
		checkZ2 = (int)(transform_.position_.z - 0.3f);
		if (pStage_->IsWall(checkX1, checkZ1) == true ||
			pStage_->IsWall(checkX2, checkZ2) == true) {
			//������O�ɖ߂�
			transform_.position_.z = (float)((int)prevPosition_.z) + 0.3f;	//�����ȉ��؂�̂ā�
																			//0.3(���@���a)�𑫂�

		}
	}
	//-------------------------------------------
/*================================================*/
#endif



}

//�`��
void Enemy::Draw()
{
}

//�J��
void Enemy::Release()
{
}