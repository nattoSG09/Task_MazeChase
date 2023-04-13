#include "MiniMap.h"
#include "Engine/Image.h"
const float MapSTDPosX = -0.98f;
const float MapSTDPosY = 0.158f;

/*--------------MiniMapObjectクラスの説明--------------
・画面端にミニマップを配置する
・16*16のサイズまでのCSVデータを
---------------------------------------------*/

//コンストラクタ
MiniMap::MiniMap(GameObject* parent)
	: GameObject(parent, "MiniMap"), hPict_{}, obj_(0),Width_(0),Height_(0),Width_Max(0),Height_Max(0)
	,type_(0),Ppos(0,0,0),Cpos(0, 0, 0),Epos(0, 0, 0),DrawX_(0),DrawY_(0),Opasity_(0),Size_(0)
	,PicSize(0, 0, 0),PicPos(0,0,0)
{
}

//初期化
void MiniMap::Initialize()
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
		const char* fileName[] = { "P_MapFloor.png","P_MapWall.png","P_MapPlayer.png","P_Coin2.png","P_Enemy.png"};
		for (int i = 0; i < Mini_MAX; i++)
		{
			hPict_[i] = Image::Load(fileName[i]);
			assert(hPict_[i] >= 0);
		}
	}
	
	//画像データ設定
	{
		PicSize = { 0.0125f,0.0125f,0.0125f };
		PicPos = { -0.96f,0.18f,0.0f };

		MapTrans.scale_ = { 0.015f,0.015f,0.015f };

		PlayerTrans.scale_ = PicSize;
		PlayerTrans.position_ = PicPos;
		
		CoinTrans.scale_ = PicSize;
		CoinTrans.position_ = PicPos;
		
		EnemyTrans.scale_ = PicSize;
		EnemyTrans.position_ = PicPos;
	}
}

//更新
void MiniMap::Update()
{
}

//描画
void MiniMap::Draw()
{
	//player情報の取得
	{
		Player* p = (Player*)FindObject("Player");
		Ppos.x = p->GetPosition().x;
		Ppos.y = p->GetPosition().z;
	}

	//coin情報の取得
	#if 1
		Coin* c = (Coin*)FindObject("Coin");
		if (c != nullptr) {
			for (int i = 0; i < 30; i++) {
				Cpos = Global::CoinPos[i];
				//Cpos.y = Global::CoinPos.z[i];

				CoinTrans.position_.x = ((Cpos.x - (3 - 0.97)) * 0.0125f) - 0.97f;
				CoinTrans.position_.y = ((Cpos.y - (3 - 0.2)) * 0.024f) + 0.2f;

				//Coinを表示
				//2枚目以降の表示をしたい
				Image::SetTransform(hPict_[Mini_COIN], CoinTrans);
				Image::Draw(hPict_[Mini_COIN]);
			}
		}
	#endif
	//enemy情報の取得
	{
		Enemy* e = (Enemy*)FindObject("Enemy");
		Epos.x = e->GetPosition().x;
		Epos.y = e->GetPosition().z;
	}

	//ミニマップを表示
	{
		for (Width_ = 0; Width_ < Width_Max; Width_++)//横
		{
			for (Height_ = 0; Height_ < Height_Max; Height_++)//縦
			{
				MapTrans.position_.x = (Width_ * 0.025f) + (MapSTDPosX + (DrawX_ / 10)); 
				MapTrans.position_.y = (Height_ * 0.048f) + (MapSTDPosY + (DrawY_ / 10));

				//いま何行目か*どれくらい間隔開けるか - 初期値

				type_ = ptable_[Width_][Height_];

				Image::SetTransform(hPict_[type_], MapTrans);
				Image::Draw(hPict_[type_]);
			}
		}

	//((Playerの位置-(3-位置))*加速度)±位置
		PlayerTrans.position_.x = ((Ppos.x - (3 - 0.97)) * 0.0125f) - 0.97f + (DrawX_ / 10);
		PlayerTrans.position_.y = ((Ppos.y - (3 - 0.2)) * 0.024f) + 0.2f + (DrawY_ / 10);

		EnemyTrans.position_.x = ((Epos.x - (3 - 0.97)) * 0.0125f) - 0.97f + (DrawX_ / 10);
		EnemyTrans.position_.y = ((Epos.y - (3 - 0.2)) * 0.024f) + 0.2f + (DrawY_ / 10);

	}
	
	//Playerを表示
	Image::SetTransform(hPict_[Mini_PLAYER], PlayerTrans);
	Image::Draw(hPict_[Mini_PLAYER]);

	
		
	//ラスト1枚を消したい
	#if 0
	if (c == nullptr) {
		hPict_[Mini_COIN]->KillMe();
	}
	else {
		Image::SetTransform(hPict_[Mini_COIN], CoinTrans);
		Image::Draw(hPict_[Mini_COIN]);
	}
	#endif


	//Enemyを表示
	//Enemy用の画像が欲しい
	Image::SetTransform(hPict_[Mini_ENEMY], EnemyTrans);
	Image::Draw(hPict_[Mini_ENEMY]);
}

//開放
void MiniMap::Release()
{
}

//画面上での表示場所を決める関数
void MiniMap::DrawPosition(float _posX, float _posY)
{
	this->DrawX_ = _posX; 
	this->DrawY_ = _posY;
}

//画面上での表示サイズを決める関数
void MiniMap::DrawSize(float _size)
{
	this->Size_ = _size;
}

//不透明度を変更する関数
void MiniMap::ChengeOpacity(int _Opa)
{
	this->Opasity_ = _Opa;
}
