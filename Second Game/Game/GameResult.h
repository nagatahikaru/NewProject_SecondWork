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
	SoundSource* m_GameResultBGM = nullptr;      //ÉQÅ[ÉÄíÜÇÃBGM
	int m_Score;
};

