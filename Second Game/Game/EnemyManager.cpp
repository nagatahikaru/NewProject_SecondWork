#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Player.h"

//�ȉ��̃R�[�h�̓v�[�����g�����G�l�~�[�Ǘ��̎�����ł��B
EnemyManager::EnemyManager()
{

}

// �I��
EnemyManager::~EnemyManager()
{
	// �G�l�~�[�v�[���̃G�l�~�[��S�č폜
	//auto�͎������_���s���A����Ŏ����I��e��Enemy*�^�ɂ��Ă����
	for (auto e : m_EnemyPool) {
		DeleteGO(e);
	}
	//����Ńv�[���̒��g����ɂ���
	m_EnemyPool.clear();
}

// �J�n
bool EnemyManager::Start()
{
	//�����Ńv�[���ɓ���鐔�����߂�
	//����̓G��20�̂ɂ��Ă݂�
	InitEnemyPool(20);
	m_Player = FindGO<Player>("m_Player");
	return true;
}

// �G�l�~�[�v�[���̏�����
void EnemyManager::InitEnemyPool(int poolSize)
{
	for (int i = 0; i < poolSize; i++)
	{
		auto enemy = NewGO<Enemy>(0, "enemy");// �V�����G�l�~�[�𐶐�	
		//e->Deactivate();               // ��A�N�e�B�u�ɂ���
		m_EnemyPool.push_back(enemy);// �v�[���ɒǉ�
	}
}

// �X�V
void EnemyManager::Update()
{
	m_Player = FindGO<Player>("m_Player");
	if (m_Player == nullptr)
	{
		return;
	}
	Spawn();
}

void EnemyManager::Spawn()
{
	// �o�ߎ��Ԃ����Z
	m_SpawnTimer += g_gameTime->GetFrameDeltaTime();

	// 3�b���ƂɓG���o��
	if (m_SpawnTimer >= 3) {
		
		auto enemy = GetInactiveEnemy();
		// ������A�N�e�B�u�ȃG�l�~�[��������
		if (enemy) {
			//��A�N�e�B�u�ȃG�l�~�[�̒�����A�N�e�B�u�ɂ���
			enemy->Activate();
			m_isActive = true;		     // �A�N�e�B�u�t���O�𗧂Ă�
			enemy->m_Hp = enemy->m_Maxhp; // �o�����ɑ̗͑S��
			m_EnemyCount++;
		}
		m_SpawnTimer = 0.0f; // �^�C�}�[�����Z�b�g
	}
}

// ��A�N�e�B�u�ȃG�l�~�[���擾
Enemy* EnemyManager::GetInactiveEnemy()
{
	// �G�l�~�[�v�[���𑖍�
	for (auto enemy : m_EnemyPool)
	{
		if (!enemy->IsActive()) return enemy;// ��A�N�e�B�u�ȃG�l�~�[��Ԃ�

	}
	return nullptr; // �S���o�����Ȃ疳��
}