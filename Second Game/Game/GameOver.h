#pragma once

class GameResult;

class GameOver:public IGameObject
{
public:
	GameOver();
	~GameOver();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	
	SpriteRender m_spriteRender;
};

