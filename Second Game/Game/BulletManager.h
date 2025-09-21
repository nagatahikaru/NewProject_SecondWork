#pragma once

class Bullet;

class BulletManager:public IGameObject
{
public:
	BulletManager();
	~BulletManager();
	bool Start();
	void Update();
	void FireBullet(const Vector3& pos, const Vector3& dir);
	bool IsBulletStuck() const { return m_isBulletStuck; }
	void InitBulletPool(int poolSize);
	Bullet* GetInactiveBullet();


	std::vector<Bullet*> m_BulletPool;
	Bullet* m_bullet;
	bool m_isBulletStuck = false;
};

