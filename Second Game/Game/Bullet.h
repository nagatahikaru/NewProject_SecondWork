#pragma once

class Player;
class Enemy;

class Bullet:public IGameObject
{
public:
	Bullet();
	~Bullet();
	bool Start();
	void Update();
	void Fire(const Vector3& startPos, const Vector3& dir, float speed);
	void Atk();	
	void Reload();
	void Render(RenderContext& rc);


	std::vector<Enemy*> m_EnemyPool;
	Player* m_Player;
	Vector3 m_Position;
	Vector3 m_Direction;
	float m_Speed = 0.0f;
	Vector3 m_MoveSpeed;
	ModelRender m_ModelRender;
	int m_Atk=0;

};

