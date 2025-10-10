#pragma once

class GameTiter;
class UI;


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
	UI* m_UI = nullptr;
	FontRender   m_fontRender;
	SoundSource* m_GameResultBGM = nullptr;      //ÉQÅ[ÉÄíÜÇÃBGM
	int m_Score;
};

