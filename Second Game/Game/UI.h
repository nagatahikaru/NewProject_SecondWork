#pragma once

class Game;
class Player;
class GameResult;

class UI:public IGameObject
{
public:
	UI();
	~UI();
	bool Start()override;
	void Update()override;
	void SetHpbarPos();
	void SetScorePos();
	void SetTimePos();
	void Render(RenderContext& rc)override;

public:
	SpriteRender m_HpGauge;//体力ゲージ
	SpriteRender m_BulletGauge[6];//弾数ゲージ
	SpriteRender m_BulletSilhouette[6];//弾丸のシルエット
	FontRender m_Score;//スコア
	FontRender m_Time;//時間
	Game* m_Game;
	Player* m_Player;
	GameResult* m_Gameresult;
	float m_LimitTime;//制限時間
	int m_BulletCount;//弾数
	int m_Scores;


};

