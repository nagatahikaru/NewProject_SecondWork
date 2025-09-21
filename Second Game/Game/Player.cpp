#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "GameCamera.h"
#include "GameResult.h"

Player::Player()
{
	
}

Player::~Player()
{

}

bool Player::Start()
{
	//アニメーションクリップをロードする。
	m_AnimationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_AnimationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_ModelRender.Init("Assets/modelData/unityChan.tkm", m_AnimationClips, enAnimationClip_Num, enModelUpAxisY);
	m_ModelRender.SetShadowCasterFlag(false);
	m_Position = Vector3{ 200.0f,0.0f,50.0f };
	m_ModelRender.SetPosition(m_Position);
	m_CharacterController.Init(25.0f, 75.0f, m_Position);
	m_Bulletmanager = FindGO<BulletManager>("bulletmanager");
	
	m_BulletCount = 6; //弾丸の初期数
	m_PlayreHp = 100;
	return true;
}

void Player::Update()
{
	m_GameCamera = FindGO<GameCamera>("m_GameCamera");
	if(m_GameCamera ==nullptr)
	{
		return;
	}
	Rotation();	
	ATK();
	Score();
	Move();
}

void Player::Move()
{
	//xzの移動速度を0.0fにする
	m_MoveSpeed.x = 0.0f;
	m_MoveSpeed.z = 0.0f;

	//左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持って来る。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//ｙ方向には移動させない
	forward.y = 0.0f;
	right.y = 0.0;

	//左スティックの入力量と200.0fを乗算
	right *= stickL.x * 200.0f;
	forward *= stickL.y * 200.0f;

	//移動速度にスティックの入力量を加算する。
	m_MoveSpeed += right + forward;

	//Bボタンが押されている間は移動速度を2倍にする
	if (g_pad[0]->IsPress(enButtonB) && m_Time <= m_TimeLimit)
	{
		m_MoveSpeed.x *= SpeedBaika; // Bボタンが押されている間は右方向の速度を2倍にする
		m_MoveSpeed.z *= SpeedBaika; // Bボタンが押されている間は前方向の速度を2倍にする
		m_Time = m_Time + g_gameTime->GetFrameDeltaTime(); // 経過時間を更新
	}
	else
	{
		//経過時間を減算していく
		m_Time = m_Time - g_gameTime->GetFrameDeltaTime();
	}
	if (m_Time < 0.0f) // 経過時間が0以下になったら
	{
		m_Time = 0.0f; // 経過時間を0にリセット
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
	}
	//キャラクターコントローラーを使って座標を移動させる
	m_Position = m_CharacterController.Execute(m_MoveSpeed, g_gameTime->GetFrameDeltaTime());
}

void Player::ATK()
{
	m_Bulletmanager = FindGO<BulletManager>("m_bulletManager");
	if (!m_Bulletmanager) {
		printf("BulletManager が nullptr です！\n");
	}

	//クールタイム
	if (m_Atktime > 0) {
		m_Atktime -= g_gameTime->GetFrameDeltaTime();
		if (m_Atktime < 0) m_Atktime = 0;
	}

	//攻撃処理,Lスティック押し込みで弾丸発射
	if (g_pad[0]->IsTrigger(enButtonX)&& m_BulletCount>0)
	{
		if(m_Atktime<=0)		
		{
			// プレイヤーの向き（前方向ベクトル）
			Vector3 dir(0, 0, 1);      // Z+方向を基準の前向きにする
			Quaternion rot = m_Rotation;
			rot.Apply(dir);
			dir.Normalize(); // 念のため正規化

            // プレイヤーの位置（少し前にずらすと自然）
            Vector3 pos = m_Position + dir * 10.0f + Vector3(0, 10.0f, 0);

            // 発射命令
			m_Bulletmanager->FireBullet(pos, dir);
			m_BulletCount--;
			m_Atktime = 0.5;
		}
	}

	//弾丸のリロード時間と弾丸の補充
	//Jボタンを長押しでリロード
	if (g_pad[0]->IsPress(enButtonA)&&m_BulletCount >= 0)
	{		
		//リロードタイム
		m_ReloadTime += g_gameTime->GetFrameDeltaTime();
	    if (m_ReloadTime >= 1 && m_BulletCount <6)
	    {
			int i = 6 - m_BulletCount;//補充する弾丸の数
			m_BulletCount += i; //弾丸補充
			auto bullet = FindGO<Bullet>("bullet");
			bullet->Reload();		  
			m_ReloadTime = 0;
	    }
	}
}

void Player::Rotation()
{
	//カメラの前方向を持ってくる
	Vector3 forward = g_camera3D->GetForward();
	forward.y = 0;
	forward.Normalize();
	//向きをセット
	m_Rotation.SetRotationYFromDirectionXZ(forward);
	//絵描きさんに回転を教える
	m_ModelRender.SetRotation(m_Rotation);
	
}

void Player::Score()
{
	float time = g_gameTime->GetFrameDeltaTime();
	int intTime = static_cast<int>(time); // 小数点以下を切り捨て
	int Fiftytimes = 50;//50倍
	//GameResult->m_Score += intTime * Fiftytimes;//スコア加算	
}

void Player::Render(RenderContext& rc)
{
	m_GameCamera = FindGO<GameCamera>("m_GameCamera");
	if (m_GameCamera == nullptr)
	{
		return;
	}
	wchar_t bu[129];
	m_fontRender.SetPosition({ -600.0f,300.0f,0.0f });
	//表示する色を設定する。
	m_fontRender.SetColor(g_vec4White);
	// スコアを取得
	int Count = m_BulletCount;
	// 座標を文字列に変換   正数表記は%d
	swprintf(bu, 129, L"弾数: %d",Count);
	// テキストをセット
	m_fontRender.SetText(bu);
	// フォント描画
	m_fontRender.Draw(rc);

	// 弾詰まり表示
	if (m_Bulletmanager && m_Bulletmanager->IsBulletStuck()) {
		m_fontRender.SetPosition({ -600.0f,400.0f,0.0f });
		m_fontRender.SetColor({ 1.0f, 0.0f, 0.0f, 1.0f }); // 赤色
		m_fontRender.SetText(L"弾詰まり！");
		m_fontRender.Draw(rc);
	}
}

