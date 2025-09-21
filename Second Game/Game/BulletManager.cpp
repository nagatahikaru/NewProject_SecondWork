#include "stdafx.h"
#include "BulletManager.h"
#include "Bullet.h"

BulletManager::BulletManager()
{

}


BulletManager::~BulletManager()
{
	for (auto bullet : m_BulletPool) {
		DeleteGO(bullet);
		bullet = nullptr;
	}
	m_BulletPool.clear();
}

bool BulletManager::Start()
{
	InitBulletPool(12);
	return true;
}

void BulletManager::Update()
{

}

void BulletManager::FireBullet(const Vector3& pos, const Vector3& dir)
{
	auto bullet = GetInactiveBullet();
	if (bullet) {
		bullet->Fire(pos, dir, 4000.0f);// 弾を発射
	}
}


void BulletManager::InitBulletPool(int poolSize)
{
	for (int i = 0; i < poolSize; i++)
	{
		auto m_bullet = NewGO<Bullet>(0, "bullet");// 新しい弾丸を生成
		m_bullet->Deactivate();         // 仮想的な非表示メソッド		
		m_BulletPool.push_back(m_bullet);// プールに追加

	}
}

Bullet* BulletManager::GetInactiveBullet()
{
	for (auto m_bullet : m_BulletPool)
	{
		if (!m_bullet->IsActive())m_isBulletStuck = false; return m_bullet;// 非アクティブな弾丸を返す
	}
	m_isBulletStuck = true;
	return nullptr; // 全員出撃中なら無し
}