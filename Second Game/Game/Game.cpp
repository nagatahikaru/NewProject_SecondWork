#include "stdafx.h"
#include "Game.h"
#include "GameOver.h"
#include "GameClear.h"
#include "GameCamera.h"
#include "GameLoad.h"
#include "Player.h"
#include "BackGround.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "SoundManager.h"

Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_Player);
	DeleteGO(m_BackGround);
	DeleteGO(m_GameCamera);
	DeleteGO(m_Enemymanager);
	DeleteGO(m_Bulletmanager);
}

bool Game::Start()
{		
	m_GameCamera=NewGO<GameCamera>(0, "m_GameCamera");//ゲームカメラ生成
	SkyCube* sky = NewGO<SkyCube>(0);                // スカイクラスのインスタンスを生成
	sky->SetLuminance(0.2f);                         // スカイの輝度を設定
	sky->SetScale(10000.0f);                       // スカイのスケールを設定
	sky->SetType(enSkyCubeType_NightToon_2);         // スカイのタイプを設定
	g_renderingEngine->DisableTonemap();             // トーンマッピングを無効にする
	m_Player = FindGO<Player>("m_Player");
	m_Time = 120; // 制限時間を60秒に設定
	SoundManager* soundManager = FindGO<SoundManager>("soundManager");       //
	m_GameBGM = soundManager->PlayingSound(Sound::enSound_InGameBGM, true, 1.0f);//
	return true;
}

void Game::Update()
{
	if (m_Player == nullptr)return;

	m_Time -= g_gameTime->GetFrameDeltaTime();
	//プレイヤーの体力が0以下でゲームオーバー
	
    if (m_Player->m_PlayreHp<=0)
	{
		if (m_GameBGM != nullptr)
		{
			m_GameBGM->Stop();
			m_GameBGM = nullptr;
		}
		//ゲーム終了
		NewGO<GameOver>(0, "m_Gameover");
		DeleteGO(this); // ゲーム画面を削除
	}
	//時間切れでゲームクリア
	if (m_Time <= 0)
	{
		if (m_GameBGM != nullptr)
		{
			m_GameBGM->Stop();
			m_GameBGM = nullptr;
		}
		NewGO<GameClear>(0, "m_Gameclear");
		DeleteGO(this);
	}
}

void Game::Render(RenderContext& rc)
{
	
	// 描画する文字列を用意
	wchar_t bu[129];
	m_fontRender.SetPosition({ -600.0f,150.0f,0.0f });
	//表示する色を設定する。
	m_fontRender.SetColor(g_vec4White);
	// エネミーの座標を取得
	int Time = m_Time;
	// 座標を文字列に変換   
	swprintf(bu, 129, L"Time: %d",Time);
	// テキストをセット
	m_fontRender.SetText(bu);
	// フォント描画
	m_fontRender.Draw(rc);
}