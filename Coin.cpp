#include "Coin.h"

//�R���X�g���N�^
Coin::Coin(GameObject* parent)
	: GameObject(parent, "Coin"),hModel_(-1),pStageMap_(nullptr)
{
}

Coin::Coin(){}

//������
void Coin::Initialize()
{
	//���f���̃��[�h
	hModel_ = Model::Load("F_Coin.fbx");
	assert(hModel_ >= 0);

	//�R���C�_�[
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
	AddCollider(collision);

	//Scale_size
	transform_.scale_ = { 0.5f,0.5f ,0.5f };

	//rotate
	transform_.rotate_.x = 90;

	//stage���̎擾
	pStageMap_ = (StageMap*)FindObject("StageMap");

	//�X�|�[���ʒu�̐ݒ�
	{
		//�Œ�X�|�[��
		//transform_.position_ = { 11.0f,0.5f,11.0f };

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
			transform_.position_ = { spawnX , 0.5f , spawnZ };
		}
		#endif
	}
}

//�X�V
void Coin::Update()
{
	//���邭��܂킷
	transform_.rotate_.y++;
}

//�`��
void Coin::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Coin::Release()
{
}
