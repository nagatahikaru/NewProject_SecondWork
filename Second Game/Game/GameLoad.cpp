#include "stdafx.h"
#include "GameLoad.h"
#include "Game.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "BackGround.h"
#include "Player.h"
#include "SoundManager.h"

GameLoad::GameLoad()
{

}

GameLoad::~GameLoad()
{

}

bool GameLoad::Start()
{

	m_spriteRender.Init("Assets/sprite/GameLoad_2.DDS", 1920.0f, 1080.0f);

	m_LoadBarSpriteRender.Init("Assets/sprite/Enemy.DDS", 100.0f, 150.0f);

	m_unitySpriteRender.Init("Assets/sprite/Sign_No.DDS", 200.0f, 200.0f);
	m_unitySpriteRender.SetPosition(Vector3(-50.0f, -125.0f, 0.0f));

	m_unity1SpriteRender.Init("Assets/sprite/Sign_Okay.DDS", 200.0f, 200.0f);
	m_unity1SpriteRender.SetPosition(Vector3(-50.0f, -125.0f, 0.0f));
	SoundManager* soundManager = FindGO<SoundManager>("soundManager");       //
	m_GameLoadBGM = soundManager->PlayingSound(Sound::enSound_LoadBGM, true, 1.0f);//
	NewGO<BackGround>(0, "m_BackGround");//背景生成
	NewGO<Player>(0, "m_Player");//プレイヤー生成
	NewGO<BulletManager>(0, "m_bulletManager");//6発の弾丸を生成
	NewGO<EnemyManager>(0, "m_enemyManager");//20体の敵を生成
	/*m_Maxnewgocount = 26;
	m_newgocount = 0;*/
	return true;
}

void GameLoad::Update()
{

	
	// ここにロード処理を実装
	m_Loadtimer += g_gameTime->GetFrameDeltaTime();
	
	int unityFrame = (int)(m_Loadtimer * 3) % 2; // 0または1を交互に切り替える
	if (unityFrame == 0)
	{
		m_showUnity = true; // ユニティちゃんの表示フラグをtrueに設定
	}
	else
	{
		m_showUnity = false; // ユニティちゃんの表示フラグをfalseに設定
	}

	//時間経過でロードバーを伸ばす。
	float scale = 1.0f + m_Loadtimer * 1.534;
	if (scale > 15.0f) scale = 15.0f; // 最大15倍まで
	//スプライトが左から右に伸びるようにXの位置を補正する
	float wide = 100.0f * scale;
	//スプライトの大きさと位置を設定
	m_LoadBarSpriteRender.SetScale(Vector3(scale, 1.15f, 1.0f));
	//スプライトの中心が画面中央になるように位置を調整
	m_LoadBarSpriteRender.SetPosition(Vector3(-815.0f + wide / 2.0f, -292.0f, 0.0f));

	if (m_Loadtimer > 15)
	{
		if (m_GameLoadBGM != nullptr)
		{
			m_GameLoadBGM->Stop();
			m_GameLoadBGM = nullptr;
		}
		// ロードが完了したらゲームを開始
		NewGO<Game>(0, "m_game");
		DeleteGO(this);
		return;
	}
	LoadBre();
	m_LoadBarSpriteRender.Update();
}

void GameLoad::LoadBre()
{	
	//wchar_t text[129];
	//if (m_Loadtimer < 4) {
	//	swprintf_s(text, _countof(text), L"ユニティちゃん移動中.");
	//}
	//else if (m_Loadtimer < 6) {
	//	swprintf_s(text, _countof(text), L"ユニティちゃん移動中..");
	//}
	//else if (m_Loadtimer < 8) {
	//	swprintf_s(text, _countof(text), L"ユニティちゃん移動中...");
	//}
	//m_DrawFont.SetText(text);// フォントのテキストを設定
	//m_DrawFont.SetPosition({ -400.0f, -400.0f, 100.0f });// フォントの位置を設定
	//m_DrawFont.SetScale(1.5f);// フォントの大きさを設定
	//m_DrawFont.SetColor(g_vec4White);// フォントの色を設定
	//m_unitySpriteRender.Update();// ユニティちゃんのスプライトを更新
	//m_unity1SpriteRender.Update();// ユニティちゃんのスプライトを更新
}

void GameLoad::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_LoadBarSpriteRender.Draw(rc);
	if (m_showUnity == true)
	{
		m_unitySpriteRender.Draw(rc);
	}
	else
	{
		m_unity1SpriteRender.Draw(rc);
	}

	
	// フォントの描画
	m_DrawFont.Draw(rc);
}