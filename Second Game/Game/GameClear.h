#pragma once

class GameResult;

class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	SoundSource* m_GameClearBGM = nullptr;//�N���ABGM
	SpriteRender m_spriteRender;
	FontRender m_fontRender;
};

