#include "StageObject.h"
#include "Engine/Model.h"

//コンストラクタ
StageObject::StageObject(GameObject* parent)
	: GameObject(parent, "StageObject"), obj_(0)
{
}

//初期化
void StageObject::Initialize()
{
	//ファイルネームを入れる配列
	const char* fileName[] = { "Floor.fbx","Wall.fbx" };

	for (int i = 0; i < OBJ_MAX; i++)
	{
		//モデルデータのロード
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}
	transform_.scale_ = { 2,2,2 };
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