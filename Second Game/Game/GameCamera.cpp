#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
GameCamera::GameCamera()
{
}
GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{
	// カメラの初期化処理
	m_toCameraPos.Set(0.0f, 0.0f, -1.0f);
	// プレイヤーのオブジェクトを取得
	m_Player = FindGO<Player>("m_Player");

	//
	g_camera3D->SetNear(1.0f); // カメラの近くのクリッピング面
	g_camera3D->SetFar(100000.0f); // カメラの遠くのクリッピング面
	return true;
}
void GameCamera::Update()
{
	if (m_Player == nullptr)
	{
		return; // プレイヤーが見つからない場合は何もしない
	}
	//カメラの更新
	//注視点を更新
	Vector3 target = m_Player->m_Position;
	//プレイヤーの足元からちょっと上に注視点を設定
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_toCameraPos;// 現在のカメラ位置
	//パッドの入力を取得
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y軸の回転を計算
	Quaternion qRot;// 回転を表すクォータニオン
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x); // 左スティックのX軸入力でY軸回転
	qRot.Apply(m_toCameraPos); // カメラ位置に回転を適用
	//X軸の回転を計算
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos); // 左スティックのY軸入力でX軸回転
	axisX.Normalize(); // 正規化
	qRot.SetRotationDeg(axisX, 1.3f * y); // X軸の回転を設定
	qRot.Apply(m_toCameraPos); // カメラ位置に回転を適用
	//カメラの回転の上限をチェックする
	//注視点から視点までのベクトルを制止化する
	//正規化すると、ベクトルの大きさが1になる
	//大きさが1になるということは、ベクトルから強さがなくなり方向のみの情報となるということ
	Vector3 toPosDir = m_toCameraPos;// 注視点からカメラ位置までのベクトル
	toPosDir.Normalize();// 正規化
	if (toPosDir.y < -0.2f)//Y軸回転の上限
	{
		m_toCameraPos = toCameraPosOld;// 回転を適用しない
	}
	else if (toPosDir.y > 0.9f)
	{
		m_toCameraPos = toCameraPosOld; // 回転を適用しない
	}
	//視点を計算する
	Vector3 Pos = target + m_toCameraPos; // 注視点にカメラ位置を加算して視点を計算
	//
	g_camera3D->SetTarget(target); // カメラの注視点を設定
	g_camera3D->SetPosition(Pos); // カメラの位置を設定
	g_camera3D->Update(); // カメラの更新
}
