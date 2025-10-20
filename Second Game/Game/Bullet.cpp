#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

bool Bullet::Start()
{
	m_ModelRender.Init("Assets/modelData/Bullet_2.tkm", nullptr);
	return true;
}

// Bullet.cpp
void Bullet::Fire(const Vector3& pos, const Vector3& dir, float speed,const Quaternion& rot)
{
	m_Position = pos;
	m_Direction = dir;
	m_Speed = speed;
	Activate();
	m_ModelRender.SetPosition(m_Position);
	m_ModelRender.SetRotation(rot);
}

void Bullet::Update()
{
	Atk();
	Reload();
}


void Bullet::Atk()
{
	float dt = g_gameTime->GetFrameDeltaTime();
	m_Position += m_Direction * m_Speed * dt;
	m_ModelRender.SetPosition(m_Position);
	m_ModelRender.Update();
	auto enemy = FindGO<Enemy>("enemy");
	if (enemy == nullptr) return;
	// 弾の位置と敵の位置の差を計算
	Vector3 toEnemy = enemy->m_Position - m_Position;
	float distance = toEnemy.Length(); // 距離を計算
	if (distance < 20.0f) // 衝突判定の閾値
	{
		m_Atk =100 /*rand() % 50 + 51*/; //50~100のランダムな攻撃力
		enemy->m_Hp -= m_Atk; // 敵の体力を減少
		this->Deactivate(); // 弾を非アクティブにする
	}
}

void Bullet::Reload()
{
	int magnification = 800;
	m_Speed -= g_gameTime->GetFrameDeltaTime() * magnification;
	if (m_Speed <= 0.0f)	
	{
		Deactivate();
	}
	
}
void Bullet::Render(RenderContext& rc)
{
	if (!m_isActive) return; // 非アクティブなら描画スキップ
	// モデルの描画処理
	m_ModelRender.Draw(rc); // モデルを描画
	wchar_t bu[129];
	m_BulletPos.SetPosition({ 0.0f,300.0f,0.0f });
	//表示する色を設定する。
	m_BulletPos.SetColor(g_vec4White);
	// エネミーの座標を取得
	Vector3 pos = m_Position;
	// 座標を文字列に変換   
	swprintf(bu, 129, L"Pos:x=%.1f,y=%.1f,z=%.1f ", pos.x,pos.y,pos.z);
	// テキストをセット
	m_BulletPos.SetText(bu);
	// フォント描画
	m_BulletPos.Draw(rc);

}