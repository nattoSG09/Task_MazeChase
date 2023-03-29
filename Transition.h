
#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"

enum {
	FADE_IN = 0,
	FADE_OUT = 1,
};

//�e�X�g�V�[�����Ǘ�����N���X
class Transition : public GameObject
{
private:
	//�摜�ԍ����i�[
	int hPict_;

	//�s�����x���i�[
	int Opacity_;

	//�����Ԃ��i�[
	int Move_;
	bool Active_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Transition(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�t�F�[�h�C������֐�
	void FadeIN();

	//�t�F�[�h�A�E�g����֐�
	void FadeOUT();

	//��ʑJ�ڂ��J�n����֐�
	void TransStart(int _move);
};