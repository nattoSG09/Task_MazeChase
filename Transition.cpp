#include "Transition.h"

// �R���X�g���N�^
Transition::Transition(GameObject* parent)
    : GameObject(parent, "Transition"), hPict_(0), Opacity_(0), Move_(0), Active_(false)
{
}

// ������
void Transition::Initialize()
{
    // �摜�̃��[�h
    hPict_ = Image::Load("P_Transition.png");
    assert(hPict_ >= 0);

    // �s�����x��0����255�̐��l�ŊǗ�����Ă���
    Opacity_ = 255;
}

// �X�V
void Transition::Update()
{
    switch (Move_)
    {
    case FADE_IN:
        FadeIN();
        break;
    case FADE_OUT:
        FadeOUT();
        break;
    }
}

// �`��
void Transition::Draw()
{
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);
    Image::SetAlpha(hPict_, Opacity_);
}

// �J��
void Transition::Release()
{
}

// �t�F�[�h�C������֐� 255->0�ɂ���
void Transition::FadeIN()
{
    if (Opacity_ > 0)
    {
        Opacity_ -= 5;
    }
    else
    {
        Opacity_ = 0;
        Move_ = 0;
        Active_ = false;
    }
}

// �t�F�[�h�A�E�g����֐� 0->255�ɂ���
void Transition::FadeOUT()
{
    if (Opacity_ < 255)
    {
        Opacity_ += 5;
    }
    else
    {
        Opacity_ = 255;
        Move_ = 0;
        Active_ = false;
    }
}

// ��ʑJ�ڂ��J�n����֐�
void Transition::Start(int move)
{
    if (!Active_)
    {
        Active_ = true;
        Move_ = move;
    }
}

bool Transition::isOpacity(int _num){
    return (Opacity_ == _num);
}
