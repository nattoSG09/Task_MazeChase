#include "MiniMap.h"
#include "Engine/Image.h"
/*--------------MiniMap�N���X�̐���--------------
�E��ʒ[�Ƀ~�j�}�b�v��z�u���� ���܂�ɖ���
�ق��̂Ƃ��낳����ĂȂ����牽������G���[�͂�����K���ɖ��������Ă�����
---------------------------------------------*/

//�R���X�g���N�^
MiniMap::MiniMap(GameObject* parent)
	: GameObject(parent, "MiniMap"),hMapFloor_(-1),hMapPlayer_(-1),hMapWall_(-1)
{
}

//������
void MiniMap::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hMapFloor_ = Image::Load("MapFloor.png");
	assert(hMapFloor_ >= 0);
	hMapPlayer_ = Image::Load("MapWall.png");
	assert(hMapPlayer_ >= 0);
	hMapWall_ = Image::Load("MapPlayer.png");
	assert(hMapWall_ >= 0);
}

//�X�V
void MiniMap::Update()
{
}

//�`��
void MiniMap::Draw()
{
	Image::SetTransform(hMapFloor_, transform_);
	Image::Draw(hMapFloor_);
	Image::SetTransform(hMapPlayer_, transform_);
	Image::Draw(hMapPlayer_);
	Image::SetTransform(hMapWall_, transform_);
	Image::Draw(hMapWall_);
}

//�J��
void MiniMap::Release()
{
}
