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
	//モデルを横に向ける
	Quaternion rot;
	rot.SetRotationX(Math::DegToRad(90.0f));
	m_ModelRender.SetRotation(rot);
	m_Position = m_Position + Vector3(0.0f, 1.0f, 0.0f); //少し上にずらす
	m_ModelRender.SetPosition(m_Position);
	

	return true;
}

// Bullet.cpp
void Bullet::Fire(const Vector3& pos, const Vector3& dir, float speed)
{
	m_Position = pos;
	m_Direction = dir;
	m_Speed = speed;
	Activate();

	m_ModelRender.SetPosition(m_Position);

	// 弾のモデルも進行方向に回転させたい場合
	Quaternion rot;
	rot.SetRotationYFromDirectionXZ(Vector3(m_Direction.x, 0.0f, m_Direction.z));
	m_ModelRender.SetRotation(rot);
}

void Bullet::Update()
{
	float dt = g_gameTime->GetFrameDeltaTime();
	m_Position += m_Direction * m_Speed * dt;
	m_ModelRender.SetPosition(m_Position);
	m_ModelRender.Update();
	Atk();
	Reload();
}


void Bullet::Atk()
{
	auto enemy = FindGO<Enemy>("enemy");
	if (enemy == nullptr) return;
	// 弾の位置と敵の位置の差を計算
	Vector3 toEnemy = enemy->m_Position - m_Position;
	float distance = toEnemy.Length(); // 距離を計算
	if (distance < 20.0f) // 衝突判定の閾値
	{
		m_Atk = rand() % 50 + 51; //50~100のランダムな攻撃力
		enemy->m_Hp -= m_Atk; // 敵の体力を減少
		this->Deactivate(); // 弾を非アクティブにする
	}
}

void Bullet::Reload()
{
	if (m_Speed == 0.0f)return;
	if (m_Position.z > 2000.0f || m_Position.z < -200.0f ||
		m_Position.x > 1000.0f || m_Position.x < -1000.0f)
	{		
		Deactivate();
	}
}
void Bullet::Render(RenderContext& rc)
{
	if (!m_isActive) return; // 非アクティブなら描画スキップ
	// モデルの描画処理
	m_ModelRender.Draw(rc); // モデルを描画
}