#include "Enemy.h"

const int FPS = 60;

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

	//Enemy�����ݒ�
	{
		//�X�|�[���ʒu�̐ݒ�
		{

			//�Œ�X�|�[��
			//EnemyTrans_.position_ = { 11.0f,0.0f,11.0f };

			//�����_���X�|�[��
			#if 1
			{
				float spawnX = 0.0f, spawnZ = 0.0f;
				bool ok = true;


				//spawnX = (float)(rand() % 16 + 0) * 2 - 1;//rand() %�͈�+�ŏ��l;
				//spawnZ = (float)(rand() % 16 + 0) * 2 - 1;//rand() %�͈�+�ŏ��l;

				while (ok)
				{
					if (pStageMap_->IsWall(spawnX, spawnZ)) {
						spawnX = (float)(rand() % 16 + 0) * 2 - 1;//rand() %�͈�+�ŏ��l;
						spawnZ = (float)(rand() % 16 + 0) * 2 - 1;//rand() %�͈�+�ŏ��l;
					}
					else {
						break;
					}
				}
				EnemyTrans_.position_ = { spawnX , 0.0f , spawnZ };
			}
			#endif

		}

		//���f���X�P�[���̐ݒ�
		EnemyTrans_.scale_ = { 0.8f,0.8f,0.8f };

		//�A�j���[�V�����̐ݒ�
		Model::SetAnimFrame(hModel_, 0, 60, 1);
	}
}

//�X�V
void Enemy::Update()
{
	//�ۑ�
	{
	//�����_���X�|�[������
	//��(�ǂɖ��܂炸�ɏo������悤�ɂ��鏈��) �ł���

	//Enemy���ǂ�F�����āA�ǂɂԂ�������ǂ��悯�Ēʂ鏈��

	//player��Enemy�̎��E�ɓ�������Ǐ]

	//Corider���Ȃ񂩕t���Ȃ�
	}

	//Enemy�̓��쏈��
	{
		//Player���m����
		#if 1
		{
			// �G�L�����N�^�[�̌�����\���x�N�g�����擾����

			XMFLOAT3 EnemyDir;
			XMVECTOR vMove = { 0.0f,0.0f,0.1f,0.0f };
			XMMATRIX EnemyTransMatrix = XMMatrixRotationY(XMConvertToRadians(EnemyTrans_.rotate_.y));

			XMStoreFloat3(&EnemyDir, XMVector3TransformCoord(vMove, EnemyTransMatrix));

			Player* pPlayer = (Player*)FindObject("Player");
			int hPlayer = pPlayer->GetModelHandle();

			//���C�L���X�g�f�[�^��p�ӂ���
			
			//���C�L���X�g.�X�^�[�g��p��
			XMFLOAT3 VsPos = { EnemyTrans_.position_.x,EnemyTrans_.position_.y + 1, EnemyTrans_.position_.z, };
			
			//���C�L���X�g�f�[�^(player)
			RayCastData vrPlayer;
			vrPlayer.start = VsPos;   
			vrPlayer.dir = EnemyDir;
			Model::RayCast(hPlayer, &vrPlayer);

			//flag_Find��"false"�̊ԁAEnemy�̌����Ă�������Ƀ��C�L���X�g�����
			if (flag_Find == false)
			{
				if (vrPlayer.hit) {
					//Player�ɓ���������flag_Find��"true"�ɂ���
					flag_Find = true;
					Debug::Log("o", true);
				}
				else {
					Debug::Log("x", true);
				}
			}

			//��莞�Ԍo�߂�flag_Find��"false"�ɂ���(�������́u��苗�������v�ɕύX�̉\������)
			/*if (flag_Find == true)
			{
				CoolTime_ = 3 * FPS;
				CoolTime_--;
				if (CoolTime_ < 0) {
					flag_Find = false;
				}
			}*/
			//�����Ƃ��Ă͂����Ă邯�ǁA���̃R�[�h����enemy��1��Player�������
			//�ڐ��O���Ȃ�����@�\���ĂȂ����ۂ��������H����
		}
		#endif

		//�f�o�b�O�p�Fflag_Find
		#if 1
		{
			if (Input::IsKeyDown(DIK_U)) {
				flag_Find = false;
			}

			if (Input::IsKeyDown(DIK_I)) {
				flag_Find = true;
			}
		}
		#endif

		//�����FPlayer�𔭌��������ۂ�
		if (flag_Find) {
			//Enemy�̒Ǐ]����
			FollowingMove();
		}
		else {
			//Enemy�̜p�j����
			WanderingMove();
		}
	}

	//�f�o�b�N�p�F�����蔻��m�F
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

	//�����蔻��̏���
	boundaryCheck();
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

//Enemy�̓���F�Ǐ]
void Enemy::FollowingMove()
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

//Enemy�̓���F�p�j
void Enemy::WanderingMove()
{
		//�����Ă���������擾

		//�����Ă�������Ƀ��C�L���X�g�����

		//�����F���C�L���X�g���ǂɓ����邩�ۂ�

		//����F��������
		//���E����R�����Ƀ��C�L���X�g�����
		//���C�L���X�g��������Ȃ������ꏊ�Ɉړ�(�����ӏ��̏ꍇ�A�����_���Ɉړ�)

		//����F������Ȃ�
		//�����Ă�������Ɉړ�
}

//�ǂƂ̂����蔻�菈��
void Enemy::boundaryCheck()
{
	//�����蔻��̊e���_���\��
	int checkX1, checkX2;
	int checkZ1, checkZ2;
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

//�����F����
//��StageObject�N���X����hModel_[]�Ƃ����ϐ��z�񂩂�K�؂ȃ��f���ԍ����擾�ł��Ȃ�
/*
	���C�L���X�g�f�[�^(wall)
		RayCastData vrWall;
		vrWall.start = VsPos;
		vrWall.dir = EnemyDir;
		Model::RayCast(hWall, &vrWall);

		Debug::Log("W->");
		Debug::Log(vrWall.dist,true);
		Debug::Log("P->");
		Debug::Log(vrPlayer.dist,true);

		//flag_Find��"false"�̊ԁAEnemy�̌����Ă�������Ƀ��C�L���X�g�����
	if (flag_Find == false){
		if (vrPlayer.hit && vrPlayer.dist < vrWall.dist) {
			//Player�ɓ���������flag_Find��"true"�ɂ���
			flag_Find = true;
			Debug::Log("o", true);
		}
		else {
			Debug::Log("x", true);
		}
	}
*/