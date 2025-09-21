#pragma once

class Player;
class BackGround;
class Game;
class EnemyManager;
class BulletManager;

class GameLoad:public IGameObject
{
public:
	GameLoad();
	~GameLoad();
	bool Start();
	void Update();
	void LoadBre();
	void Render(RenderContext& rc);

	Game*          m_game;
	Player*        m_player = nullptr;       //プレイヤー
	BackGround*    m_backGround = nullptr;   //背景
	EnemyManager*  m_enemymanager = nullptr; //敵
	BulletManager* m_bulletmanager = nullptr;//弾丸
	SpriteRender   m_spriteRender;
	SpriteRender   m_LoadBarSpriteRender;
	SpriteRender   m_unitySpriteRender;
	SpriteRender   m_unity1SpriteRender;

	float m_Loadtimer = 0.0f;//ロード時間を計測するためのタイマー
	FontRender m_DrawFont; // フォントレンダラー

	bool m_showUnity = false; // ユニティちゃんの表示フラグ
	int m_Maxnewgocount = 0; // 最大生成数
	int m_newgocount = 0; // 現在の生成数

};

