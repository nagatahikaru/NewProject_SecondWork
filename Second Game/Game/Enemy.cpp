#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "EnemyManager.h"
#include "GameCamera.h"
#include <random>

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

bool Enemy::Start()
{
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);

	m_ModelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips,enModelUpAxisY);
	//ナビメッシュを構築。
	m_NvmMesh.Init("Assets/nvm/Nvm_2.tkn");
	// 乱数エンジンの初期化
	// 実行ごとに異なる乱数列を生成するため、std::random_deviceを使用
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	// 範囲 [0.0, 100.0) でfloatの乱数を生成する分布を定義
	std::uniform_real_distribution<float> dist(100.0f, 10000.0f);
	float x = dist(engine);// x座標の乱数
	float z = dist(engine);// z座標の乱数
	m_ModelRender.SetShadowCasterFlag(false);
	m_Position = Vector3{ x,0.0f,z };
	m_ModelRender.SetPosition(m_Position);
	m_CharacterController.Init(25.0f, 75.0f, m_Position);
	m_CharacterController.GetRigidBody();
	m_Player = FindGO<Player>("m_Player");
	m_GameCamera = FindGO<GameCamera>("m_GameCamera");
	SoundManager* soundManager = FindGO<SoundManager>("soundManager");       //
	m_GameATKSE = soundManager->PlayingSound(Sound::enSound_DamageSE, false, 1.0f);//敵の攻撃音
	return true;
}

void Enemy::Update()
{
	Move();
	Rotation();	
	Dead();	
}

void Enemy::Atk()
{
	if (m_Player == nullptr) return;
	m_GameATKSE->Play(false); //敵の攻撃音再生
	m_Enemyatk = rand() % 20 + 5;  //攻撃力をランダムに設定(5~25)
	//プレイヤーの体力を減らす
	m_Player->m_PlayreHp -= m_Enemyatk;

}

void Enemy::Move()
{
	
	Vector3 pos = m_Player->m_Position; //プレイヤーの位置
	Vector3 Distance = m_Position - pos;//プレイヤーとの距離
	float dist = Distance.Length();	
	PlayAnimation();

	////攻撃
	Atkinterval = Atkinterval + g_gameTime->GetFrameDeltaTime();
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

	if (dist >= 950.0f)
	{
		m_DetectionTime += g_gameTime->GetFrameDeltaTime();
		//プレイヤーを追いかける
		if(m_DetectionTime<=1.0f)
		{
			m_TargetPosition = pos;
			m_DetectionTime = 0.0f;
		}
		
		//パス探索
		m_PathFiding.Execute(
			m_Path,                     //構築されたバスの格納先
			m_NvmMesh,                  //ナビメッシュ
			m_Position,                 //開始座標
			m_TargetPosition,           //移動目標座標				
			PhysicsWorld::GetInstance(),//物理エンジン
			50.0f,                      //AIエージェントの半径
			200.0f                      //AIエージェントの高さ
		);
		//移動速度の設定		
		m_Speed = 10.5f;//移動速度を距離によって変更		

		//パスの上を移動する
		m_Position = m_Path.Move(
			m_Position, //開始座標
			m_Speed,    //移動速度
			Isend       //パス終点
		);
	}
	if(dist <=1000.0f)
	{
		m_Speed = 1.0f;//移動速度を距離によって変更
		Distance.Normalize();
		 m_Position += Distance* m_Speed * g_gameTime->GetFrameDeltaTime();
	}
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
		if(m_MoveSpeed.y < -100.0f)
		{
			Dead();
		}
	}
	PlayAnimation();
	//エネミーの位置更新
	m_ModelRender.SetPosition(m_Position);
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
	m_ModelRender.PlayAnimation(enAnimationClip_Run);
	//アニメーションを増やす用のスペース
}

void Enemy::Dead()
{	
	if(m_Position.y<-100.0f)
	{
		Deactivate();
		return;
	}
	auto bullet = FindGO<Bullet>("bullet");
	Vector3 dif=bullet->m_Position - m_Position;
	float dist = dif.Length();
	if(dist<=50.0f)
	{
		bullet->Atk();
		; //弾丸の攻撃力分体力を減らす
		if (m_Hp <= 0)
		{
			m_isActive = false;
			m_Player->m_Score += 100; //スコア加算
			Deactivate();
		}
	}
}

void Enemy::Render(RenderContext& rc)
{
	if (!m_isActive) return; // 非アクティブなら描画スキップ

	// モデルの描画処理

	m_ModelRender.Draw(rc); // モデルを描画	

//	wchar_t bu[129];
//m_fontRender.SetPosition({ -600.0f,150.0f,0.0f });
////表示する色を設定する。
//m_fontRender.SetColor(g_vec4White);
//// エネミーの座標を取得
//int EnemyCount = m_Enemymanager->m_EnemyCount;
//// 座標を文字列に変換   
//swprintf(bu, 129, L"EnemyCount: EnemyCount=%1", EnemyCount);
//// テキストをセット
//m_fontRender.SetText(bu);
//// フォント描画
//m_fontRender.Draw(rc);
}
