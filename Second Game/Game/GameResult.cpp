#include "stdafx.h"
#include "GameResult.h"
#include "GameTiter.h"

GameResult::GameResult()
{
	//背景画像
	m_spriteRender.Init("Assets/sprite/GameResult_2.DDS", 1920.0f, 1080.0f);
}

GameResult::~GameResult()
{

}

bool GameResult::Start()
{
	return true;
}

void GameResult::Score(int score)
{
	float time = g_gameTime->GetFrameDeltaTime();
	int intTime = static_cast<int>(time); // 小数点以下を切り捨て
	int Fiftytimes = 50;//50倍
	m_Score += intTime * Fiftytimes;//スコア加算	
}

void GameResult::Update()
{
	//Iボタンでタイトルへへ
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		//if (sound != nullptr)
		//{
		//	sound->Stop();
		//	sound = nullptr;
		//}
		//Result移動
		NewGO<GameTiter>(0, "m_gametiter");
		DeleteGO(this); // タイトル画面を削除
	}
}

void GameResult::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);

	wchar_t bu[129];
	m_fontRender.SetPosition({ -600.0f,300.0f,0.0f });
	//表示する色を設定する。
	m_fontRender.SetColor(g_vec4White);
	// スコアを取得
	int Count = m_Score;
	// 座標を文字列に変換   正数表記は%d
	swprintf(bu, 129, L"Score: %d", Count);
	// テキストをセット
	m_fontRender.SetText(bu);
	// フォント描画
	m_fontRender.Draw(rc);
}
