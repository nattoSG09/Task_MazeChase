#include "Item.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

//�R���X�g���N�^
Item::Item(GameObject* parent)
	: GameObject(parent, "Item"),hModel_(-1)
{
}

//������
void Item::Initialize()
{
	//���f���f�[�^�̃��[�h
	//hModel_ = Model::Load("");
	//assert(hModel_ >= 0);

	//SphereCollider* Icollision = new SphereCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), 1.0f);
	//AddCollider(Icollision);
}

//�X�V
void Item::Update()
{
}

//�`��
void Item::Draw()
{
	//�A�C�e���̕`��
	//Model::SetTransform(hModel_, transform_);
	//Model::Draw(hModel_);
}

//�J��
void Item::Release()
{
}


//������������
void Item::OnCollision(GameObject* pTarget)
{
	//�v���C���[�Ɠ���������
	//if (pTarget->GetObjectName() == "Player")
	//{
		//�R�C��������
	//	KillMe();
	//}
}
