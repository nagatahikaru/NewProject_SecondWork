#include "stdafx.h"
#include "UI.h"
#include "Game.h"
#include "Player.h"
#include "GameResult.h"

namespace {
	const Vector3 bulletPos[6] = {
		Vector3(-850.0f, -410.0f,0.0f), 
		Vector3(-810.0f, -410.0f,0.0f),
		Vector3(-770.0f, -410.0f,0.0f), 
		Vector3(-730.0f, -410.0f,0.0f),
		Vector3(-690.0f, -410.0f,0.0f), 
		Vector3(-650.0f, -410.0f,0.0f)
	};

	const Vector3 InGameScorePos = { -896.0f, 300.0f, 0.0f };
	const Vector3 ResultScorePos = { 896.0f, 300.0f, 0.0f };
}


UI::UI()
{

}

UI::~UI()
{

}

bool UI::Start()
{
	m_Game = FindGO<Game>("m_game");
	m_Gameresult = FindGO<GameResult>("m_gameresult");
	m_Player = FindGO<Player>("m_Player");
	m_Player->m_UI = FindGO<UI>("m_UI");
	for (int i = 0; i < 6; i++)
	{		
		m_BulletGauge[i].Init("Assets/sprite/Bullet.DDS", 40.0f, 70.0f);
		m_BulletSilhouette[i].Init("Assets/sprite/BulletSilhouette.DDS", 40.0f, 70.0f);
		m_BulletGauge[i].SetPosition(Vector3(bulletPos[i]));
		m_BulletSilhouette[i].SetPosition(Vector3(bulletPos[i]));
	}
	m_HpGauge.Init("Assets/sprite/Enemy.DDS", 50.0f, 50.0f);
	return true;
}

void UI::Update()
{
	// Playerがまだ見つかっていない場合は再検索
	if (m_Player == nullptr) {
		m_Player = FindGO<Player>("m_Player");
		return; // まだ見つからなければ何もしない	
	}

	// Playerが見つかってから初めてUI処理を行う
	SetHpbarPos();
	SetTimePos();
	SetScorePos();
}


void UI::SetHpbarPos()
{

	int scale = m_Player->m_PlayreHp;
	if (scale > 10.0f) scale = 10.0f; // 最大10倍まで
	//スプライトが右から左に伸るようにXの位置を補正する
	float wide = 100.0f * scale;
	//スプライトの大きさと位置を設定
	m_HpGauge.SetScale(Vector3(scale, 1.15f, 1.0f));
	//スプライトの中心が画面中央になるように位置を調整
	m_HpGauge.SetPosition(Vector3(-980.0f + wide / 2.0f, -480.0f, 0.0f));
	m_HpGauge.Update();
}

void UI::SetScorePos()
{
	Vector3 scorePos = Vector3(0.0f, 0.0f, 0.0f);

	if (m_Game) {
		scorePos = InGameScorePos;
	}
	if (m_Gameresult) {
		scorePos = ResultScorePos;
	}

	wchar_t be[129];
	m_Score.SetPosition(scorePos);
	m_Score.SetColor(g_vec4White);
	int Score = m_Scores;
	swprintf(be, 129, L"Score:%d", Score);
	m_Score.SetText(be);
}

void UI::SetTimePos()
{
	if (!m_Game)
	{
		return;
	}
	m_LimitTime = m_Game->m_Time;
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
}

void UI::Render(RenderContext& rc)
{	
	m_Score.Draw(rc);

	if (!m_Player)
	{
		return;
	}
	// フォント描画
	m_Time.Draw(rc);
	int bulletCount = m_Player->m_BulletCount;
	for (int i = 0; i < bulletCount; i++) {

		m_BulletGauge[i].Update();
		m_BulletGauge[i].Draw(rc);
	}
	for (int i = 5; i >= bulletCount; i--) {

		m_BulletSilhouette[i].Update();
		m_BulletSilhouette[i].Draw(rc);
	}
	m_HpGauge.Draw(rc);
}