#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Player.h"

//以下のコードはプールを使ったエネミー管理の実装例です。
EnemyManager::EnemyManager()
{

}

// 終了
EnemyManager::~EnemyManager()
{
	// エネミープールのエネミーを全て削除
	//autoは自動推論を行う、それで自動的にeをEnemy*型にしてくれる
	for (auto e : m_EnemyPool) {
		DeleteGO(e);
	}
	//これでプールの中身を空にする
	m_EnemyPool.clear();
}

// 開始
bool EnemyManager::Start()
{
	//ここでプールに入れる数を決める
	//今回の敵は20体にしてみた
	InitEnemyPool(20);
	m_Player = FindGO<Player>("m_Player");
	return true;
}

// エネミープールの初期化
void EnemyManager::InitEnemyPool(int poolSize)
{
	for (int i = 0; i < poolSize; i++)
	{
		auto enemy = NewGO<Enemy>(0, "enemy");// 新しいエネミーを生成	
		//e->Deactivate();               // 非アクティブにする
		m_EnemyPool.push_back(enemy);// プールに追加
	}
}

// 更新
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
	// 経過時間を加算
	m_SpawnTimer += g_gameTime->GetFrameDeltaTime();

	// 3秒ごとに敵を出す
	if (m_SpawnTimer >= 3) {
		
		auto enemy = GetInactiveEnemy();
		// もし非アクティブなエネミーがいたら
		if (enemy) {
			//非アクティブなエネミーの中からアクティブにする
			enemy->Activate();
			m_isActive = true;		     // アクティブフラグを立てる
			enemy->m_Hp = enemy->m_Maxhp; // 出撃時に体力全回復
			m_EnemyCount++;
		}
		m_SpawnTimer = 0.0f; // タイマーをリセット
	}
}

// 非アクティブなエネミーを取得
Enemy* EnemyManager::GetInactiveEnemy()
{
	// エネミープールを走査
	for (auto enemy : m_EnemyPool)
	{
		if (!enemy->IsActive()) return enemy;// 非アクティブなエネミーを返す

	}
	return nullptr; // 全員出撃中なら無し
}