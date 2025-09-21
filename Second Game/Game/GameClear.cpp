#include "stdafx.h"
#include "GameClear.h"
#include "GameResult.h"
#include "SoundManager.h"

GameClear::GameClear()
{

}

GameClear::~GameClear()
{

}

bool GameClear::Start()
{
	m_spriteRender.Init("Assets/sprite/GameClear_2.DDS", 1980.0f, 1080.0f);
	SoundManager* soundManager = FindGO<SoundManager>("soundManager");       //
	m_GameClearBGM = soundManager->PlayingSound(Sound::enSound_ClearBGM, true, 1.0f);//

	return true;
}

void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		if (m_GameClearBGM != nullptr)
		{
			m_GameClearBGM->Stop();
			m_GameClearBGM = nullptr;
		}
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
