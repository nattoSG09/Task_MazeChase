#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class Timer : public GameObject
{
public:
	//�X�e�[�g�p�^�[��
	enum {
		TIMER,
		STOPWATCH,
	};

	int State_;//�X�e�[�g��Ԃ��i�[����ϐ�

private:

	int Frame_;//�c�莞�Ԃ𐔂���ϐ�
	
	bool Active_;//true�̎��ɃJ�E���g�_�E��/�A�b�v����
	Text* pText;
	int DrawX_, DrawY_;//�\���ʒu

public:
	//�R���X�g���N�^
	Timer(GameObject* parent);

	//�f�X�g���N�^
	~Timer();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�X�V�F�^�C�}�[
	void TimerUpdate();

	//�X�V�F�X�g�b�v�E�H�b�`
	void StopWatchUpdate();

	//�`��
	void Draw() override;

	//�J��
	void Release() override;


	//������������Timer�֐�������������

	//�g�p����@�\��ύX����֐�
	//�����F_state�@(Timer::TIMER) or (Timer::STOPWATCH)
	void UseThis(int _state);

	//�������Ԃ�(�b)�Őݒ肷��֐�
	//�����Fseconds_(�b)
	void SetLimit(float seconds_);

	//�J�E���g���J�n����֐�
	void TimeStart();

	//�J�E���g���I������֐�
	void TimeStop();

	//�I����������m�点��֐�
	bool IsFinished();

	//���f��������m�点��֐�
	bool IsStopped();

	//��ʂ̕\���ʒu���w�肷��֐�
	//�����P�F _x (X���W)
	//�����Q�F _y (Y���W)
	void DrawPostion(int _x, int _y) { DrawX_ = _x, DrawY_ = _y; }
	//��������������������������������
};

//�g�p���l���Ă���֐�
	//��������������������������������
	////�X�g�b�v�E�H�b�`���g�p����֐�
	//void UseaStopWatch();
	////�^�C�}�[���g�p����֐�
	//void UseaTimer();
	//��������������������������������

