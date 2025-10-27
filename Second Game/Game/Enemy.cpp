#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "EnemyManager.h"
#include "GameCamera.h"
#include "SoundManager.h"
#include <random>

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

bool Enemy::Start()
{
	//m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	//m_animationClips[enAnimationClip_Run].SetLoopFlag(true);

	m_ModelRender.Init("Assets/modelData/Enemy.tkm", m_animationClips, enModelUpAxisY);
	m_ModelRender.SetShadowCasterFlag(false);

	// 初期座標をランダムに決定
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::uniform_real_distribution<float> dist(200.0f, 10000.0f);
	float x = dist(engine);
	float z = dist(engine);
	m_Position = Vector3{ x, 0.0f, z };

	// ---- ★ RigidBody（物理ボディ）設定 ----
	nsK2EngineLow::RigidBodyInitData rbInfo;
	rbInfo.pos = m_Position;
	rbInfo.rot.SetRotationY(0.0f);
	rbInfo.mass = 1.0f;                // 質量
	rbInfo.restitution = 1.0f;         // 反発係数（跳ね返り度）

	// 敵の当たり判定コライダーを作成
	auto collider = new nsK2EngineLow::SphereCollider; // もしSphereColliderが使えるなら
	collider->Create(25.0f); // 半径25
	rbInfo.collider = collider;

	m_RigidBody.Init(rbInfo);//剛体をセット
	m_RigidBody.GetBody();
	m_RigidBody.SetFriction(1.0f);//摩擦力を設定
	m_RigidBody.SetLinearFactor(1.0f, 1.0f, 1.0f);//移動可能軸を設定
	m_RigidBody.SetAngularFactor(0.0f, 1.0f, 0.0f); // Y軸回転のみ許可

	// ---- ★ CharacterControllerは不要（または補助用） ----
	// m_CharacterController.Init(25.0f, 75.0f, m_Position);

	m_Player = FindGO<Player>("m_Player");
	m_GameCamera = FindGO<GameCamera>("m_GameCamera");

	return true;
}


void Enemy::Update()
{
	Move();
	Rotation();	
	Dead();	
	PlayAnimation();
}

void Enemy::Atk()
{
	SoundManager* soundManager = FindGO<SoundManager>("soundManager");       //	
	m_GameATKSE = soundManager->PlayingSound(enSound_DamageSE, false, 1.0f);//敵の攻撃音
	m_Enemyatk = rand() % 20 + 5;  //攻撃力をランダムに設定(5~25)
	//プレイヤーの体力を減らす
	m_Player->m_PlayreHp -= m_Enemyatk;

}

void Enemy::Move()
{
	
	Vector3 pos = m_Player->m_Position; //プレイヤーの位置
	Vector3 Distance = m_Position - pos;//プレイヤーとの距離
	float dist = Distance.Length();	
	
	if (m_GameCamera != nullptr)
	{
		////攻撃
		Atkinterval += g_gameTime->GetFrameDeltaTime();
		if (dist <= 30.0f && Atkinterval == 0.5f)
		{
			Atk();
			Atkinterval = 0.0f;
			return;
		}
		if (Atkinterval > 0.5f)
		{
			Atkinterval = 0.2f;
		}
		m_Speed = 100.0f;//移動速度を距離によって変更
		Distance.Normalize();
		m_Position -= Distance * m_Speed * g_gameTime->GetFrameDeltaTime();

		//地面についていたら
		if (m_CharacterController.IsOnGround())
		{
			//重力をなくす
			m_MoveSpeed.y = 0.0f;
		}
		else//地面についていなかったら
		{
			//重力を発生させる
			const float gravety = 25.5f;//重力の定数
			m_MoveSpeed.y -= gravety;
			if (m_MoveSpeed.y < -100.0f)
			{
				Dead();
			}
		}
	}
	else
	{
		m_GameCamera=FindGO<GameCamera>("m_GameCamera");
	}
	//エネミーの位置更新
	m_ModelRender.SetPosition(m_Position);
	m_RigidBody.SetPositionAndRotation(m_Position, m_Rotation);
	Rotation();
	//エネミーの更新
	m_ModelRender.Update();
}

void Enemy::Rotation()
{
	if (m_Player == nullptr) return;
	Vector3 toPlayer = m_Player->GetPosition() - m_Position;
	toPlayer.Normalize();
	m_Rotation.SetRotationYFromDirectionXZ(toPlayer);// Y軸回りの回転を設定
	m_ModelRender.SetRotation(m_Rotation);
}

void Enemy::PlayAnimation()
{
	//m_ModelRender.PlayAnimation(enAnimationClip_Run);
	//アニメーションを増やす用のスペース
}

void Enemy::Dead(float damage)
{	
	

	if(m_Position.y<-100.0f)
	{
		Deactivate();
		return;
	}
	m_Hp -= damage;
	 //弾丸の攻撃力分体力を減らす
	if (m_Hp <= 0)
	{
		m_isActive = false;
		m_Player->m_Score += 100; //スコア加算
		Deactivate();
	}
}

void Enemy::Render(RenderContext& rc)
{
	if (!m_isActive) return; // 非アクティブなら描画スキップ

	// モデルの描画処理

	m_ModelRender.Draw(rc); // モデルを描画
}
