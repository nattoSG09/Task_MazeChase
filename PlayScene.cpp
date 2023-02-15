#include "PlayScene.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
}

//更新
void PlayScene::Update()
{
	switch (state_)
	{
	case 
	}
}

//更新・準備
void PlayScene::UpdateReady()
{
}

//更新・プレイ中
void PlayScene::UpdatePlay()
{
}

//更新・終了
void PlayScene::UpdateFinish()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}
