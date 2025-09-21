#include "stdafx.h"
#include "GameClear.h"
#include "GameResult.h"

GameClear::GameClear()
{

}

GameClear::~GameClear()
{

}

bool GameClear::Start()
{
	m_spriteRender.Init("Assets/sprite/GameClear_2.DDS", 1980.0f, 1080.0f);
	return true;
}

void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		//if (sound != nullptr)
		//{
		//	sound->Stop();
		//	sound = nullptr;
		//}
		//ResultˆÚ“®
		NewGO<GameResult>(0, "m_gameresult");
		DeleteGO(this); // ƒ^ƒCƒgƒ‹‰æ–Ê‚ğíœ
	}
}

void GameClear::Render(RenderContext &rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}
