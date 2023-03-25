#include "MiniMapObject.h"


/*--------------MiniMapObjectクラスの説明--------------
・画面端にミニマップを配置する あまりに未完
ほかのところさわってないから何かしらエラーはいたら適当に無効化していいよ
---------------------------------------------*/

//コンストラクタ
MiniMapObject::MiniMapObject(GameObject* parent)
	: GameObject(parent, "MiniMapObject"), hPict_{ -1,-1,-1 }, obj_(0)
	,Width_(0),Height_(0),Width_Max(0),Height_Max(0),type_(0),Ppos(0,0,0)
{
}

//初期化
void MiniMapObject::Initialize()
{

	//table情報の取得
	{
		StageMap* pStageMap = (StageMap*)FindObject("StageMap");
		ptable_ = pStageMap->GetTable_();
		Width_Max = pStageMap->GetWidth();
		Height_Max = pStageMap->GetHeight();
	}
	
	//仮置き
	#if 0
	{
		MiniMapCSV.Load("M_Map1.csv");//マップデータ読み込み

		Width_Max = MiniMapCSV.GetWidth();//CSVの横、縦の要素数を取得
		Height_Max = MiniMapCSV.GetHeight();

		ptable_.resize(Width_Max, vector<int>(Height_Max, 0));//初期化

		for (int x = 0; x < Width_Max; x++)//CSVデータを2次元配列table_に代入
			for (int y = 0; y < Height_Max; y++)
				ptable_[x][y] = MiniMapCSV.GetValue(x, ((Height_Max - 1) - y));
	}
	#endif

	//画像データのロード
	{
		const char* fileName[] = { "P_MapFloor.png","P_MapWall.png","P_MapPlayer.png" };
		for (int i = 0; i < Mini_MAX; i++)
		{
			hPict_[i] = Image::Load(fileName[i]);
			assert(hPict_[i] >= 0);
		}
	}
	
	//画像データ設定
	{
		MapTrans.scale_ = { 0.015f,0.015f,0.015f };
		PlaTrans.scale_ = { 0.0125f,0.0125f,0.0125f };
		PlaTrans.position_ = { -0.96f,0.18f,0.0f };
	}
}

//更新
void MiniMapObject::Update()
{
	//player情報の取得
	{
		Player* p = (Player*)FindObject("Player");
		Ppos.x = p->GetPPos().x;
		Ppos.y = p->GetPPos().z;
	}

	//PlaTrans.position_.x = (Ppos.x - 2.04*3.82) / 18;
	//PlaTrans.position_.y = (Ppos.y - 2.615 / 2.45  ) / 18;
	//Ppos.x - def *rev / MovSense 
	//PlaTrans.position_.x = ((Ppos.x - 2.04)* -1)*0.01 ;
	//PlaTrans.position_.y = ((Ppos.y - 2.615)*1)*0.01   ;

	PlaTrans.position_.x = ((Ppos.x - 2.04f)*0.0125f) - 0.97f;
	PlaTrans.position_.y = ((Ppos.y - 2.2)*0.0235f) + 0.18f;
	
	//((Playerの位置-(3-初期値))*ちょうどいい値)±platransの初期値(多少誤差ある)
}

//描画
void MiniMapObject::Draw()
{

	//ミニマップを表示
	{
		for (Width_ = 0; Width_ < Width_Max; Width_++)//横
		{
			for (Height_ = 0; Height_ < Height_Max; Height_++)//縦
			{
				/*MapTrans.position_.x = (Width_  * 0.02f)  - 0.98f;
				MapTrans.position_.y = (Height_ * 0.02f)  + 0.378f;*/

				MapTrans.position_.x = (Width_ * 0.025) - 0.98f;
				MapTrans.position_.y = (Height_ * 0.046f) + 0.158f;
				//いま何行目か*どれくらい間隔開けるか - 初期値

				type_ = ptable_[Width_][Height_];

				Image::SetTransform(hPict_[type_], MapTrans);
				Image::Draw(hPict_[type_]);
			}
		}
	}
	
	//Playerを表示
	Image::SetTransform(hPict_[2], PlaTrans);
	Image::Draw(hPict_[2]);
}

//開放
void MiniMapObject::Release()
{
}