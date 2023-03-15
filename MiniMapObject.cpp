#include "MiniMapObject.h"
#include "Player.h"
#include "Engine/Image.h"
#include "Engine/CsvReader.h"
#include "Engine/Input.h"
/*--------------MiniMapObjectクラスの説明--------------
・画面端にミニマップを配置する あまりに未完
ほかのところさわってないから何かしらエラーはいたら適当に無効化していいよ
---------------------------------------------*/

//コンストラクタ
MiniMapObject::MiniMapObject(GameObject* parent)
	: GameObject(parent, "MiniMapObject"), hPict_{ -1,-1,-1 }, obj_(0),pStage_(nullptr)
	,Width_(0),Height_(0),Width_Max(0),Height_Max(0),type_(0),Ppos(0,0,0)
{
}

//初期化
void MiniMapObject::Initialize()
{
	MiniMapCSV.Load("M_SW_Map1.csv");

	Width_Max = MiniMapCSV.GetWidth();
	Height_Max = MiniMapCSV.GetHeight();

	table_.resize(Width_Max, vector<int>(Height_Max, 0));

	for (int x = 0; x < Width_Max; x++)
		for (int y = 0; y < Height_Max; y++)
			table_[x][y] = MiniMapCSV.GetValue(x, ((Height_Max - 1) - y));

	const char* fileName[] = { "MapFloor2.png","MapWall2.png","MapPlayerRedFrame.png" };
	for (int i = 0; i < Mini_MAX; i++)
	{
		hPict_[i] = Image::Load(fileName[i]);
		assert(hPict_[i] >= 0);
	}
	MapTrans.scale_ = { 0.015f,0.015f,0.015f };


	PlaTrans.scale_ = { 0.0125f,0.0125f,0.0125f };
	PlaTrans.position_ = { -0.96f,0.38f,0.0f };
	
	
}

//更新
void MiniMapObject::Update()
{
	
	Player* p = (Player*)FindObject("Player");
	Ppos.x = p->GetPPos().x;
	Ppos.y = p->GetPPos().z;

	/*PlaTrans.position_.x = (Ppos.x - 2.04*3.82) / 18;
	PlaTrans.position_.y = (Ppos.y - 2.615 / 2.45  ) / 18;*/

	//Ppos.x - def *rev / MovSense 

	//PlaTrans.position_.x = ((Ppos.x - 2.04)* -1)*0.01 ;
	//PlaTrans.position_.y = ((Ppos.y - 2.615)*1)*0.01   ;

	PlaTrans.position_.x = ((Ppos.x - 2.04f)*0.0125f) - 0.97f;
	PlaTrans.position_.y = ((Ppos.y - 2.2)*0.0235f) + 0.378f;

	if (Input::IsKey(DIK_LEFT)) {
		PlaTrans.position_.x -= 0.1f;
	}
	if (Input::IsKey(DIK_RIGHT)) {
		PlaTrans.position_.x += 0.1f;
	}
	if (Input::IsKey(DIK_UP)) {
		PlaTrans.position_.y += 0.1f;
	}
	if (Input::IsKey(DIK_DOWN)) {
		PlaTrans.position_.y -= 0.1f;
	}
	
}

//描画
void MiniMapObject::Draw()
{
	for (Width_ = 0; Width_ < Width_Max; Width_++)
	{
		for (Height_ = 0; Height_ < Height_Max; Height_++)
		{
			/*MapTrans.position_.x = (Width_  * 0.02f)  - 0.98f;
			MapTrans.position_.y = (Height_ * 0.02f)  + 0.378f;*/

			MapTrans.position_.x = (Width_ * 0.025) - 0.98f;
			MapTrans.position_.y = (Height_ * 0.045f) + 0.358f;

			type_ = table_[Width_][Height_];

		Image::SetTransform(hPict_[type_], MapTrans);
		Image::Draw(hPict_[type_]);
		}

	}
	Image::SetTransform(hPict_[2], PlaTrans);
	Image::Draw(hPict_[2]);

}

//開放
void MiniMapObject::Release()
{
}