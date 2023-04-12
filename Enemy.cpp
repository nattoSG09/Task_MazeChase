#include "Enemy.h"

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"),hModel_(-1),pStageMap_(nullptr),F_TargetPosition_{},W_TargetPosition_{}
	,flag_Find(0),CoolTime_(0),FixedTime_(0)
{
}

//������
void Enemy::Initialize()
{
	hModel_ = Model::Load("F_Enemy(move).fbx");
	assert(hModel_ >= 0);

	BoxCollider* collision = new BoxCollider(XMFLOAT3(0,1,0), XMFLOAT3(1, 2, 1));
	AddCollider(collision);

	//stage���̎擾
	pStageMap_ = (StageMap*)FindObject("StageMap");

	//EnemyTarget�ݒ�
	{
		//bool okk=true;
		//while (okk)
		//{
		//	if (pStageMap_->IsWall(wTargetX,wTargetZ)) {
		//		wTargetX = (float)(rand() % 16 + 0) * 2 - 1;//rand() %�͈�+�ŏ��l;
		//		wTargetZ = (float)(rand() % 16 + 0) * 2 - 1;//rand() %�͈�+�ŏ��l;
		//	}
		//	else {
		//		okk = false;
		//	}
		//}
	}
	
	//Enemy�����ݒ�
	{
		//�X�|�[���ʒu�̐ݒ�
		{

			//�Œ�X�|�[��
			//transform_.position_ = { 11.0f,0.0f,11.0f };

			//�����_���X�|�[��
			#if 1
			{
				float spawnX = 0.0f , spawnZ = 0.0f;
				bool ok = true;

				while (ok)
				{
					if (pStageMap_->IsWall(spawnX, spawnZ)) {
						spawnX = (float)(rand() % 16 + 0) * 2 - 1;//rand() %�͈�+�ŏ��l;
						spawnZ = (float)(rand() % 16 + 0) * 2 - 1;//rand() %�͈�+�ŏ��l;
					}
					else {
						ok = false;
					}
				}
				transform_.position_ = { spawnX , 0.0f , spawnZ };
			}
			#endif

		}

		//���f���X�P�[���̐ݒ�
		transform_.scale_ = { 0.8f,0.8f,0.8f };
		transform_.rotate_.y = rand()/180;

		//�A�j���[�V�����̐ݒ�
		Model::SetAnimFrame(hModel_, 0, 60, 1);
	}

	//Player���������܂ł̎��Ԃ�������
	CoolTime_ = 3 * FPS;

	//WayPoint�̏�����
	WayPoint = transform_.position_;
}

//�X�V
void Enemy::Update()
{
	//�ۑ�
	{
	//�����_���X�|�[������
	//��(�ǂɖ��܂炸�ɏo������悤�ɂ��鏈��) = �N���A�I�I

	//Enemy���ǂ�F�����āA�ǂɂԂ�������ǂ�����Ēʂ鏈�� = ��� 

	//player��Enemy�̎��E�ɓ�������Ǐ] = �N���A�I�I

	//Corider���Ȃ񂩕t���Ȃ� = �N���A�I�I
	}

	//���Ԃ��X�V
	FixedTime_++;

	//Enemy�̓��쏈��
	{
		//Player���m����
		#if 0
		{
			// �G�L�����N�^�[�̌�����\���x�N�g�����擾����

			XMFLOAT3 EnemyDir;
			XMVECTOR vMove = { 0.0f,0.0f,0.1f,0.0f };
			XMMATRIX EnemyTransMatrix = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

			XMStoreFloat3(&EnemyDir, XMVector3TransformCoord(vMove, EnemyTransMatrix));

			Player* pPlayer = (Player*)FindObject("Player");
			int hPlayer = pPlayer->GetModelHandle();

			StageMap* pStageMap = (StageMap*)FindObject("StageMap");
			
			XMFLOAT3 PlayerPosition_ = pPlayer->GetPosition();
			

			//���C�L���X�g.�X�^�[�g��p��
			XMFLOAT3 VsPos = { transform_.position_.x,transform_.position_.y + 1, transform_.position_.z, };
			
			//���C�L���X�g�f�[�^(player)
			RayCastData vrPlayer;
			vrPlayer.start = VsPos;   
			vrPlayer.dir = EnemyDir;
			Model::RayCast(hPlayer, &vrPlayer);

			//�f�o�b�N�p�F���C�L���X�g�f�[�^
			#if 0
			{
				Debug::Log("P->");
				Debug::Log(vrPlayer.dist, true);
			}
			#endif

			//flag_Find��"false"�̊ԁAEnemy�̌����Ă�������Ƀ��C�L���X�g�����
			if (flag_Find == false)
			{
				if (vrPlayer.hit && !pStageMap->HasWallBetween(transform_.position_, PlayerPosition_)){
					//true�ɂȂ邱�Ƃ�Player��Ǐ]����
						flag_Find = true;
				}
				else {
				}
			}

			//��莞�Ԍo�߂�flag_Find��"false"�ɂ���(�������́u��苗�������v�ɕύX�̉\������)
			if (flag_Find == true)
			{
				CoolTime_--;
				if (CoolTime_ < 0) {
					flag_Find = false;
				}
			}
			else {
				CoolTime_ = 10 * FPS;
			}
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
		if (pStageMap_->IsWall(transform_.position_.x, transform_.position_.z)) {
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
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Enemy::Release()
{
}

// original function

//�Q�̍��W���r����֐�
bool Enemy::isCloser(XMFLOAT3 A_, XMFLOAT3 B_, XMFLOAT3 T_)
{
	bool closest = false;
	float disA = (abs(T_.x) + abs(T_.z)) - (abs(A_.x) + abs(A_.z));
	float disB = (abs(T_.x) + abs(T_.z)) - abs(B_.x) + abs(B_.z);

	if (disA < disB) {
		closest = true;
	}
	return (closest);
}

//�S�̍��W���r���āA�ł��ړI�n�ɋ߂��ꏊ��Ԃ��֐�
XMFLOAT3 Enemy::FindShortestDistance(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c, XMFLOAT3 d, XMFLOAT3 Target)
{
	XMFLOAT3 closePos = a;
	if (isCloser(b, closePos, Target)) {
		closePos = b;
	}
	if (isCloser(c, closePos, Target)) {
		closePos = c;
	}
	if (isCloser(d, closePos, Target)) {
		closePos = d;
	}

	return (closePos);
}

//�i�s����ړI�n�����肷��ꏊ��Ԃ��֐�
XMFLOAT3 Enemy::DIJKSTRA(XMFLOAT3 NowPos_, XMFLOAT3 TargetPos_)
{
	XMFLOAT3 E, W, N, S;
	//�E 
	E = { NowPos_.x + 2.0f,0,NowPos_.z };
	//�� 
	W = { NowPos_.x - 2.0f,0,NowPos_.z };
	//�� 
	N = { NowPos_.x,0,NowPos_.z + 2.0f };
	//��O 
	S = { NowPos_.x,0,NowPos_.z - 2.0f };

	XMFLOAT3 CclosePos = FindShortestDistance(E, W, N, S, TargetPos_);
	return CclosePos;
}

//�ړI�n�ɓ���������True��Ԃ��֐�
bool Enemy::isArrival(XMFLOAT3 NowPos_, XMFLOAT3 TargetPos_)
{
	bool Arr = false;
	if (NowPos_.x == TargetPos_.x && NowPos_.z == TargetPos_.z) {
		Arr = true;
	}
	return (Arr);
}

//Enemy�̓���F�Ǐ]
void Enemy::FollowingMove()
{
	

	//�_�C�N�X�g���@��p�����Ǐ]����(���s)
	#if 1
	{
		//����
		{	
			//isArraival()�֐��ɂ�铞�����f���ł��ĂȂ��̂��ȁ[
		}

		//�ړI�n���擾(player�̈ʒu)
		Player* p = (Player*)FindObject("Player");
		F_TargetPos = p->GetPosition();

		//�o�R�n�ɂ��ǂ���܂�
		if (!isArrival(transform_.position_, F_TargetPos)) {

			//Enemy��WayPoint�̍����v�Z����
			XMFLOAT3 deltaPosition = XMFLOAT3(
				WayPoint.x - transform_.position_.x,
				0,
				WayPoint.z - transform_.position_.z
			);

			//Enemy�̐i�s�������v�Z����
			XMVECTOR EnemyDir = XMVector3Normalize(XMLoadFloat3(&deltaPosition));

			//Enemy�̈ړ����x
			float Speed = 0.05f;

			//Enemy��WayPoint�Ɍ������Ĉړ�������
			transform_.position_.x += (XMVectorGetX(EnemyDir) * Speed);
			transform_.position_.y += (XMVectorGetY(EnemyDir) * Speed);
			transform_.position_.z += (XMVectorGetZ(EnemyDir) * Speed);

			//�x�N�g���̒��������߂�
			XMVECTOR vLength = XMVector3Length(EnemyDir);
			float length = XMVectorGetX(vLength);

			if (length != 0)
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

				transform_.rotate_.y = XMConvertToDegrees(angle);
			}
		}
		//���ǂ蒅������
		else {
			//TargetPos�܂ł�WayPoint���擾
			XMFLOAT3 WayPoint = DIJKSTRA(transform_.position_, F_TargetPos);
		}
	}
	#endif

	//�����̒Ǐ]����(���ݎg�p�𒆎~) 23/04/12�`
	#if 0
	{
		//player�̈ʒu���擾����
		Player* p = (Player*)FindObject("Player");
		F_TargetPosition_ = p->GetPosition();

		//Enemy��player�̍����v�Z����
		XMFLOAT3 deltaPosition = XMFLOAT3(
			F_TargetPosition_.x - transform_.position_.x,
			F_TargetPosition_.y - transform_.position_.y,
			F_TargetPosition_.z - transform_.position_.z
		);

		//Enemy�̐i�s�������v�Z����
		XMVECTOR EnemyDir = XMVector3Normalize(XMLoadFloat3(&deltaPosition));

		//Enemy�̈ړ����x
		float Speed = 0.05f;

		//Enemy��Target�Ɍ������Ĉړ�������
		transform_.position_.x += (XMVectorGetX(EnemyDir) * Speed);
		transform_.position_.y += (XMVectorGetY(EnemyDir) * Speed);
		transform_.position_.z += (XMVectorGetZ(EnemyDir) * Speed);

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

			transform_.rotate_.y = XMConvertToDegrees(angle);
		}

	}
	#endif

}

//Enemy�̓���F�p�j
void Enemy::WanderingMove()
{
	
	//�G�̏�����ݒ�
	#if 1
	{
		//�ړI�n�̍Đݒ�

		float TargetX = 0, TargetZ = 0;
		bool ok = true;

		if (Every_nMinitues(5)){
			while (ok)
			{
				if (pStageMap_->IsWall(TargetX, TargetZ)) {
					Debug::Log("�ǂ������I", true);
					TargetX = (float)(rand() % 16 + 0) * 2 - 1;//rand() %�͈�+�ŏ��l;
					TargetZ = (float)(rand() % 16 + 0) * 2 - 1;//rand() %�͈�+�ŏ��l;
				}
				else {
					ok = false;
				}
			}
			W_TargetPosition_ = { TargetX , 0 ,TargetZ };
			Debug::Log("�ړI�n���ă^�[�Q�b�g���܂����B", true);
		}
		
	}
	#endif

	//Enemy��player�̍����v�Z����
	XMFLOAT3 deltaPosition = XMFLOAT3(
		W_TargetPosition_.x - transform_.position_.x,
		W_TargetPosition_.y - transform_.position_.y,
		W_TargetPosition_.z - transform_.position_.z
	);

	//Enemy�̐i�s�������v�Z����
	XMVECTOR EnemyDir = XMVector3Normalize(XMLoadFloat3(&deltaPosition));

	//Enemy�̈ړ����x
	float Speed = 0.04f;

	//Enemy��Target�Ɍ������Ĉړ�������
	transform_.position_.x += (XMVectorGetX(EnemyDir) * Speed);
	transform_.position_.y += (XMVectorGetY(EnemyDir) * Speed);
	transform_.position_.z += (XMVectorGetZ(EnemyDir) * Speed);

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

		transform_.rotate_.y = XMConvertToDegrees(angle);
	}

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
			checkX1 = (int)(transform_.position_.x + 0.2f);
			checkZ1 = (int)(transform_.position_.z + 0.1f);
			//���_�Q
			checkX2 = (int)(transform_.position_.x + 0.2f);
			checkZ2 = (int)(transform_.position_.z - 0.1f);

			//�Փ˂��Ă��邩�ǂ���
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				transform_.position_.x = (float)((int)transform_.position_.x) + (1.0f - 0.2f);
			}
		}
		//-------------------------------------------
		//���W�͏����_�����邩�炻���int�ɒ����Ƃ�
		//��-----------------------------------------
		{
			//���_�P
			checkX1 = (int)(transform_.position_.x - 0.2f);
			checkZ1 = (int)(transform_.position_.z + 0.1f);
			//���_�Q
			checkX2 = (int)(transform_.position_.x - 0.2f);
			checkZ2 = (int)(transform_.position_.z - 0.1f);

			//�Փ˂��Ă��邩�ǂ���
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				transform_.position_.x = (float)((int)transform_.position_.x) + 0.2f;
			}
		}
		//-------------------------------------------
		//���W�͏����_�����邩�炻���int�ɒ����Ƃ�
		//��-----------------------------------------
		{
			//���_�P
			checkX1 = (int)(transform_.position_.x + 0.1f);
			checkZ1 = (int)(transform_.position_.z + 0.2f);
			//���_�Q
			checkX2 = (int)(transform_.position_.x - 0.1f);
			checkZ2 = (int)(transform_.position_.z + 0.2f);

			//�Փ˂��Ă��邩�ǂ���
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				transform_.position_.z = (float)((int)transform_.position_.z) + (1.0f - 0.2f);
			}
		}
		//-------------------------------------------
		//���W�͏����_�����邩�炻���int�ɒ����Ƃ�
		//��-----------------------------------------
		{
			//���_�P
			checkX1 = (int)(transform_.position_.x + 0.1f);
			checkZ1 = (int)(transform_.position_.z - 0.2f);
			//���_�Q
			checkX2 = (int)(transform_.position_.x - 0.1f);
			checkZ2 = (int)(transform_.position_.z - 0.2f);
			if (pStageMap_->IsWall(checkX1, checkZ1) == true || pStageMap_->IsWall(checkX2, checkZ2) == true)
			{
				transform_.position_.z = (float)((int)transform_.position_.z) + 0.2f;
			}
		}
		//-------------------------------------------
}