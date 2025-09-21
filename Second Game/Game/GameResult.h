#pragma once

class GameTiter;

class GameResult:public IGameObject
{
public:
	GameResult();
	~GameResult();
	bool Start();
	void Score(int score);
	void Update();
	void Render(RenderContext& rc);

	
	SpriteRender m_spriteRender;
	FontRender   m_fontRender;
	int m_Score;
};

