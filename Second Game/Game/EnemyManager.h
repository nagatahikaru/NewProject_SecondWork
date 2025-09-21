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

	std::vector<Enemy*> m_EnemyPool;// �G�l�~�[�v�[��
	Player* m_Player = nullptr; // �v���C���[�ւ̎Q��

	//�ȉ��̃R�[�h�͕ʂɕK�v�Ȃ����ǁA�G�̏o���Ԋu��ς������Ƃ��Ɏg��
	float m_SpawnTimer = 0.0f;	// �G�o���^�C�}�[
	int m_EnemyCount = 0;// ���݂̓G�̐�
};

