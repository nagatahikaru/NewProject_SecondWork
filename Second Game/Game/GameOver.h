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

	SoundSource* m_GameOverBGM = nullptr;      //�Q�[������BGM
	SpriteRender m_spriteRender;
};

