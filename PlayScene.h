#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Transition.h"
#include "MiniMap.h"
#include "StageMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"
#include "Coin.h"


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
	MiniMap* MiniMap_;
	Transition* transition_;
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