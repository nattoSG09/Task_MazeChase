#pragma once

#include "Engine/GameObject.h"
#include "Engine/Image.h"

enum {
    FADE_IN = 0,
    FADE_OUT = 1,
};

class Transition : public GameObject
{
private:
    int hPict_;  // �摜�ԍ����i�[
    int Opacity_;  // �s�����x���i�[
    int Move_;  // �����Ԃ��i�[
    bool Active_;

public:
    // �R���X�g���N�^
    Transition(GameObject* parent);

    // ������
    void Initialize() override;

    // �X�V
    void Update() override;

    // �`��
    void Draw() override;

    // �J��
    void Release() override;

    // �t�F�[�h�C������֐�
    void FadeIN();

    // �t�F�[�h�A�E�g����֐�
    void FadeOUT();

    // ��ʑJ�ڂ��J�n����֐�
    void Start(int move);

    bool isOpacity(int _num);
};
