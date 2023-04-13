#pragma once
#include <vector>
using std::vector;

#include "Engine/GameObject.h"
#include "Engine/Image.h"
#include"StageMap.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include "Global.h"

enum {
	Mini_FLOOR,
	Mini_WALL,
	Mini_PLAYER,
	Mini_COIN,
	Mini_ENEMY,
	Mini_MAX,
};

class MiniMap : public GameObject
{
	CsvReader MiniMapCSV; //このクラスでCSVを受け取るための変数
	int hPict_[Mini_MAX]; // Map画像素材 0=floor,1=wall,2=player
	int obj_;//ほかの画像素材を表示する関数につかう変数
	int type_;//Map画像の種類

	XMFLOAT3 Ppos;//Playerの位置
	XMFLOAT3 Cpos;//Coinの位置
	XMFLOAT3 Epos;//Enemyの位置
	XMFLOAT3 PicSize;	//MiniMapで表示されるオブジェクトのサイズを決定
	XMFLOAT3 PicPos;	//MiniMapで表示されるオブジェクトの位置を決定

	float Width_Max, Height_Max;//CSVデータの行列の要素数
	float Width_, Height_; //forループ用のイテレータ(?)

	Transform MapTrans;		//Mapの位置などを操作するTransform型
	Transform PlayerTrans;	//Playerの位置などを操作するTransform型
	Transform CoinTrans;	//Coinの位置を管理するTransform型
	Transform EnemyTrans;	//Enemyの位置を管理するTransform型

	vector<vector<int>> ptable_;//ステージ情報を格納する二次元配列

	float DrawX_, DrawY_;
	float Size_;
	int Opasity_;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	MiniMap(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//配置するobjectを変更する関数
	void ObjectSet(int _obj) { obj_ = _obj; }


//現在使用していませんーーーーーー

	//画面上での表示場所を決める関数
	void DrawPosition(float _posX,float _posY);

	//画面上での表示サイズを決める関数
	void DrawSize(float _size);

	//不透明度を変更する関数
	void ChengeOpacity(int _Opa);
};

