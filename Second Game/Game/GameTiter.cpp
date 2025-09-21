#include "stdafx.h"
#include "GameTiter.h"
#include "GameLoad.h"
#include "SoundManager.h"

GameTiter::GameTiter()
{
	//Titerのファイルパス
	m_spriteRender.Init("Assets/sprite/GameTiter_2.DDS",1920.0f,1080.0f);
	m_fontRender.SetText(L"ゲームスタート\n""  (Jキー)");
	m_fontRender.SetPosition({ 100.0f,100.0f,0.0f });
	m_fontRender.SetScale(2.0f);
	m_fontRender.SetColor({ m_alphas,0.0f,0.0f,m_alphas });
}

GameTiter::~GameTiter()
{

}

bool GameTiter::Start()
{
	//タイトルBGM再生
	SoundManager* soundManager = FindGO<SoundManager>("soundManager");       //
	m_GameTiterBGM = soundManager->PlayingSound(Sound::enSound_ClearBGM, true, 1.0f);//
	return true;
}

void GameTiter::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (m_GameTiterBGM != nullptr)
		{
			m_GameTiterBGM->Stop();
			m_GameTiterBGM = nullptr;
		}
		//ゲーム開始
		NewGO<GameLoad>(0, "m_gameload");		
		DeleteGO(this); // タイトル画面を削除
	}
	Font();
}

void GameTiter::Font()
{
	const float fadeSpeed = 0.01f;

	if (m_fadeIns)
	{
		// フェードイン → アルファ増加（表示へ）
		m_alphas += fadeSpeed;
		if (m_alphas >= 1.0f)
		{
			m_alphas = 1.0f;
			m_fadeIns = false; // 次はフェードアウトへ
		}
	}
	else
	{
		// フェードアウト → アルファ減少（透明へ）
		m_alphas -= fadeSpeed;
		if (m_alphas <= 0.00f)
		{
			m_alphas = 0.00f;
			m_fadeIns = true; // 次はフェードインへ
		}
	}
	m_fontRender.SetColor({ m_alphas, 0, 0, m_alphas });    // タイトルテキストの透明度を更新
}

void GameTiter::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}
