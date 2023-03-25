#include "Enemy.h"


//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"),hModel_(-1),EnemyTrans_(transform_)
{
}

//������
void Enemy::Initialize()
{
	hModel_ = Model::Load("F_Enemy(move).fbx");
	assert(hModel_ >= 0);

	//stage���̎擾
	pStageMap_ = (StageMap*)FindObject("StageMap");

	//�����ʒu�̐ݒ�
	{
		//�����_���X�|�[���ł��Ȃ�
		#if 0
		{
			float spawnX, spawnZ;
			bool ok = false;
			while (ok)
			{
				spawnX = (float)(rand() % 16 + 0) * 2 + 1;//rand() %�͈�+�ŏ��l;
				spawnZ = (float)(rand() % 16 + 0) * 2 + 1;//rand() %�͈�+�ŏ��l;

				if (pStageMap_->IsWall(spawnX, spawnZ))
				{
					EnemyTrans_.position_ = { spawnX , 0.0f , spawnZ };
					ok = true;
				}
			}
		}
		#endif

		EnemyTrans_.position_ = { 10.0f,0.0f,10.0f };
		EnemyTrans_.scale_ = { 0.8f,0.8f,0.8f };
		EnemyTrans_.rotate_.y = 0;
		Model::SetAnimFrame(hModel_, 0, 60, 1);
	}

	
}

//�X�V
void Enemy::Update()
{
	//�ۑ�
	{
	//�����_���X�|�[������
	//��(�ǂɖ��܂炸�ɏo������悤�ɂ��鏈��)

	//Enemy���ǂ�F�����āA�ǂɂԂ�������ǂ��悯�Ēʂ鏈��

	//player��Enemy�̎��E�ɓ�������Ǐ]

	//Corider���Ȃ񂩕t���Ȃ�
	}
	
	//Enemy�̒Ǐ]����
	{
		//player�̈ʒu���擾����
		Player* p = (Player*)FindObject("Player");
		TargetPosition_ = p->GetPPos();

		//Enemy��player�̍����v�Z����
		XMFLOAT3 deltaPosition = XMFLOAT3(
			TargetPosition_.x - EnemyTrans_.position_.x,
			TargetPosition_.y - EnemyTrans_.position_.y,
			TargetPosition_.z - EnemyTrans_.position_.z
		);

		//Enemy�̐i�s�������v�Z����
		XMVECTOR EnemyDir = XMVector3Normalize(XMLoadFloat3(&deltaPosition));

		//Enemy�̈ړ����x
		float Speed = 0.05;

		//Enemy��Target�Ɍ������Ĉړ�������
		EnemyTrans_.position_.x += (XMVectorGetX(EnemyDir) * Speed);
		EnemyTrans_.position_.y += (XMVectorGetY(EnemyDir) * Speed);
		EnemyTrans_.position_.z += (XMVectorGetZ(EnemyDir) * Speed);

		//�x�N�g���̒��������߂�
		XMVECTOR vLength = XMVector3Length(EnemyDir);
		float length = XMVectorGetX(vLength);

		if (length != 0)//vMove�̒�����0����Ȃ��Ƃ�(�����Ă���Ƃ�)
		{
			XMVECTOR vFront = { 0,0,1,0 };//�������̃x�N�g��

			XMVECTOR vDot = XMVector3Dot(vFront, EnemyDir);
			//���̓�̃x�N�g���̓��ς����߂�
			float dot = XMVectorGetX(vDot);
			float angle = acos(dot);//�A�[�N�R�T�C���Ōv�Z�����"�����p�x"�̂ق��̊p�x�����߂�

			XMVECTOR vCross = XMVector3Cross(vFront, EnemyDir);
			//����̃x�N�g���̊O�ς����߂�
			//�O�ς�Y���O��菬����������
			if (XMVectorGetY(vCross) < 0) {
				//angle�� -1 ��������
				angle *= -1;
			}

			EnemyTrans_.rotate_.y = XMConvertToDegrees(angle);
		}
	}

	//�f�o�b�N�p
	#if 0
	{
		//Player���ǂƐڐG���Ă��邩���m�F����
		if (pStageMap_->IsWall(EnemyTrans_.position_.x, EnemyTrans_.position_.z)) {
			Debug::Log("�Z", true);
		}
		else {
			Debug::Log("��", true);
		}
	}
	#endif

	//�����蔻��̊e���_���\��
	int checkX1, checkX2;
	int checkZ1, checkZ2;

	//�����蔻��̏���
	{
		//���W�͏����_�����邩�炻���int�ɒ����Ƃ�
	//�E-----------------------------------------
		{
			//���_�P
			checkX1 = (int)(EnemyTrans_.position_.x + 0.2f);
			checkZ1 = (int)(EnemyTrans_.position_.z + 0.1f);
			//���_�Q
			checkX2 = (int)(EnemyTrans_.position_.x + 0.2f);
			checkZ2 = (int)(EnemyTrans_.position_.z - 0.1f);

			//�Փ˂��Ă��邩�ǂ���
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				EnemyTrans_.position_.x = (float)((int)EnemyTrans_.position_.x) + (1.0f - 0.2f);
			}
		}
		//-------------------------------------------
		//���W�͏����_�����邩�炻���int�ɒ����Ƃ�
		//��-----------------------------------------
		{
			//���_�P
			checkX1 = (int)(EnemyTrans_.position_.x - 0.2f);
			checkZ1 = (int)(EnemyTrans_.position_.z + 0.1f);
			//���_�Q
			checkX2 = (int)(EnemyTrans_.position_.x - 0.2f);
			checkZ2 = (int)(EnemyTrans_.position_.z - 0.1f);

			//�Փ˂��Ă��邩�ǂ���
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				EnemyTrans_.position_.x = (float)((int)EnemyTrans_.position_.x) + 0.2f;
			}
		}
		//-------------------------------------------
		//���W�͏����_�����邩�炻���int�ɒ����Ƃ�
		//��-----------------------------------------
		{
			//���_�P
			checkX1 = (int)(EnemyTrans_.position_.x + 0.1f);
			checkZ1 = (int)(EnemyTrans_.position_.z + 0.2f);
			//���_�Q
			checkX2 = (int)(EnemyTrans_.position_.x - 0.1f);
			checkZ2 = (int)(EnemyTrans_.position_.z + 0.2f);

			//�Փ˂��Ă��邩�ǂ���
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				EnemyTrans_.position_.z = (float)((int)EnemyTrans_.position_.z) + (1.0f - 0.2f);
			}
		}
		//-------------------------------------------
		//���W�͏����_�����邩�炻���int�ɒ����Ƃ�
		//��-----------------------------------------
		{
			//���_�P
			checkX1 = (int)(EnemyTrans_.position_.x + 0.1f);
			checkZ1 = (int)(EnemyTrans_.position_.z - 0.2f);
			//���_�Q
			checkX2 = (int)(EnemyTrans_.position_.x - 0.1f);
			checkZ2 = (int)(EnemyTrans_.position_.z - 0.2f);
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				EnemyTrans_.position_.z = (float)((int)EnemyTrans_.position_.z) + 0.2f;
			}
		}
		//-------------------------------------------
	}
}
//�`��
void Enemy::Draw()
{
	Model::SetTransform(hModel_, EnemyTrans_);
	Model::Draw(hModel_);
}

//�J��
void Enemy::Release()
{
}