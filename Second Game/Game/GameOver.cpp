#include "stdafx.h"
#include "GameOver.h"
#include "GameResult.h"
#include "SoundManager.h"

GameOver::GameOver()
{

	
}

GameOver::~GameOver()
{

}

bool GameOver::Start()
{
	//スプライトレンダラー初期化
	m_spriteRender.Init("Assets/sprite/GameOver_2.DDS", 1980.0f, 1080.0f);
	SoundManager* soundManager = FindGO<SoundManager>("soundManager");       //
	m_GameOverBGM = soundManager->PlayingSound(Sound::enSound_OverBGM, true, 1.0f);//ゲームオーバーBGM再生
	return true;
}

void GameOver::Update()
{
	//Lボタンでリザルトへ
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		if (m_GameOverBGM != nullptr)
		{
			m_GameOverBGM->Stop();
			m_GameOverBGM = nullptr;
		}
		//Result移動
		NewGO<GameResult>(0, "m_gameresult");
		DeleteGO(this); // タイトル画面を削除
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}