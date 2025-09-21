#pragma once

class Enemy;
class Player;

class EnemyManager:public IGameObject
{
public:
	EnemyManager();
	~EnemyManager();
	bool Start();
	void Update();
	void Spawn();
	void InitEnemyPool(int poolSize);
	Enemy* GetInactiveEnemy();

	std::vector<Enemy*> m_EnemyPool;// エネミープール
	Player* m_Player = nullptr; // プレイヤーへの参照

	//以下のコードは別に必要ないけど、敵の出現間隔を変えたいときに使う
	float m_SpawnTimer = 0.0f;	// 敵出現タイマー
	int m_EnemyCount = 0;// 現在の敵の数
};

