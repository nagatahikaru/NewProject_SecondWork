#pragma once

class Player;
class GameCamera;
class BackGround;
class GameClear;
class GameOver;
class GameLoad;
class Enemy;
class Bullet;
class EnemyManager;
class BulletManager;


//Gameシーンを管理するクラス。
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	//更新処理
	void Update();
	void Render(RenderContext& rc);



	// "*"がある時は->で　それ以外の時は"."で"*"を使わない
	Player*        m_Player= nullptr;        //プレイヤー
	BackGround*    m_BackGround = nullptr;   //背景
	EnemyManager*  m_Enemymanager = nullptr; //敵
	BulletManager* m_Bulletmanager = nullptr;//弾丸
	GameCamera*    m_GameCamera= nullptr;    //ゲームカメラ
	GameLoad*      m_GameLoad = nullptr;     //ロード画面
	SoundSource*   m_GameBGM = nullptr;      //ゲーム中のBGM
	GameClear*     m_Gameclear = nullptr;    //ゲームカメラ
	GameOver*      m_GameOver = nullptr;     //ゲームオーバー
	FontRender        m_fontRender;                //フォント
	bool exists = false;//生存フラグ
	float m_Time= 0.0f;//時間
	
	
};

