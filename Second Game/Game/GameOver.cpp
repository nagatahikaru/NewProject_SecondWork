#include "stdafx.h"
#include "GameOver.h"
#include "GameResult.h"

GameOver::GameOver()
{

	m_spriteRender.Init("Assets/sprite/GameOver_2.DDS", 1980.0f, 1080.0f);
}

GameOver::~GameOver()
{

}

bool GameOver::Start()
{
	return true;
}

void GameOver::Update()
{
	//Lボタンでリザルトへ
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		//if (sound != nullptr)
		//{
		//	sound->Stop();
		//	sound = nullptr;
		//}
		//Result移動
		NewGO<GameResult>(0, "m_gameresult");
		DeleteGO(this); // タイトル画面を削除
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}