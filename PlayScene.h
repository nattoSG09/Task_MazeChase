#pragma once
#include "Engine/GameObject.h"
#include "Timer.h"
#include "Stage.h"
#include "Player.h"
//�e�X�g�V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
public:
	enum {
		STATE_READY,
		STATE_PLAY,
		STATE_FINISH,
	};
	int state_;
private:
	Timer* Time_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�X�V�E����
	void UpdateReady();

	//�X�V�E�v���C��
	void UpdatePlay();
	
	//�X�V�E�I��
	void UpdateFinish();

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};