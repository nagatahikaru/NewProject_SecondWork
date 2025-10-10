#include "stdafx.h"
#include "UI.h"
#include "Game.h"
#include "Player.h"
#include "GameResult.h"

UI::UI()
{

}

UI::~UI()
{

}

bool UI::start()
{
	Vector2 position[6] = {
		Vector2(-896.0f, 378.0f), Vector2(-886.0f, 378.0f),
		Vector2(-876.0f, 378.0f), Vector2(-866.0f, 378.0f),
		Vector2(-856.0f, 378.0f), Vector2(-846.0f, 378.0f)
	};

	for (int i = 0; i < 6; i++)
	{
		m_BulletGauge[i].Init("Assets/sprite/Bullet.DDS", position[i].x, position[i].y);
		m_BulletSilhouette[i].Init("Assets/sprite/BulletSilhouette.DDS", position[i].x, position[i].y);

	}
	m_HpGauge.Init("Assets/sprite/Enemy.DDS", -896.0f, 504.0f);
	return true;
}

void UI::Update()
{
	m_Player = FindGO<Player>("m_Player");
	if (m_Player == nullptr)
	{
		return;
	}
	Hpbar();
}

void UI::Hpbar()
{

	int scale = m_Player->m_PlayreHp;
	if (scale > 15.0f) scale = 15.0f; // 最大15倍まで
	//スプライトが右から左に伸るようにXの位置を補正する
	float wide = 100.0f * scale;
	//スプライトの大きさと位置を設定
	m_HpGauge.SetScale(Vector3(scale, 1.15f, 1.0f));
	//スプライトの中心が画面中央になるように位置を調整
	m_HpGauge.SetPosition(Vector3(-815.0f + wide / 2.0f, -292.0f, 0.0f));
	m_HpGauge.Update();
}

void UI::Render(RenderContext& rc)
{
	m_Game = FindGO<Game>("m_game");
	m_Gameresult = FindGO<GameResult>("m_gameresult");
	Vector3 scorePos=Vector3(0.0f, 0.0f, 0.0f);
	if (m_Game)
	{
		scorePos= Vector3(-896.0f, 300.0f, 0.0f);
	}
	else if (m_Gameresult)
	{
		scorePos = Vector3(896.0, 300.0f, 0.0f);
	}
	wchar_t be[129];
	m_Score.SetPosition(scorePos);
	m_Score.SetColor(g_vec4White);
	int Score = m_Scores;
	swprintf(be, 129, L"Score:%d", Score);
	m_Score.SetText(be);
	m_Score.Draw(rc);

	
	if (m_Game == nullptr)
	{
		return;
	}	
	m_LimitTime =m_Game->m_Time;
	// 描画する文字列を用意
	wchar_t bu[129];
	m_Time.SetPosition({ 0.0f,486.0f,0.0f });
	//表示する色を設定する。
	m_Time.SetColor(g_vec4White);
	// エネミーの座標を取得
	int Time = m_LimitTime;
	// 座標を文字列に変換   
	swprintf(bu, 129, L"Time: %d", Time);
	// テキストをセット
	m_Time.SetText(bu);
	// フォント描画
	m_Time.Draw(rc);


	m_Player = FindGO<Player>("m_Player");
	if (m_Player == nullptr)
	{
		return;
	}
	for (int i = 0; i < m_Player->m_BulletCount; i++) {

		m_BulletGauge[i].Update();
		m_BulletGauge[i].Draw(rc);		
	}
	for (int j = m_Player->m_BulletCount; j < 6; j++) {
		m_BulletSilhouette[j].Update();
		m_BulletSilhouette[j].Draw(rc);		
	}

	m_HpGauge.Draw(rc);
}