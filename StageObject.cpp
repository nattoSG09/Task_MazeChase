#include "StageObject.h"
#include "Engine/Model.h"

//コンストラクタ
StageObject::StageObject(GameObject* parent)
	: GameObject(parent, "StageObject"), obj_(0),hModel_{-1,-1}
{
}

//初期化
void StageObject::Initialize()
{
	//モデルデータのロード
	{
		const char* fileName[] = { "F_Floor.fbx","F_Wall.fbx" };

		for (int i = 0; i < OBJ_MAX; i++) {
			hModel_[i] = Model::Load(fileName[i]);
			assert(hModel_[i] >= 0);
		}
	}
	
	//objectの設定
	{
		//transform_.scale_ = { 2,2,2 };
		transform_.rotate_.y = 180;
	}
	
}

//更新
void StageObject::Update()
{
}

//描画
void StageObject::Draw()
{
	Model::SetTransform(hModel_[obj_], transform_);
	Model::Draw(hModel_[obj_]);
}

//開放
void StageObject::Release()
{
}

int StageObject::GetModelHandle(int _obj)
{
	return (hModel_[_obj]);
}