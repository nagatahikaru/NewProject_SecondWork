#pragma once
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"
#include <random>
#include "SoundManager.h"

class Player;
class Bullet;
class EnemyManager;
class GameCamera;

class Enemy:public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start();
	/*void Startset();*/
	void Update();
	void Atk();
	void Move();
	void Rotation();
	void PlayAnimation();
	void Dead();	
	void Render(RenderContext& rc);

	Player* m_Player;//プレイヤーへの参照
	Bullet* m_Bullet;//弾丸への参照
	SoundSource* m_GameATKSE = nullptr; //敵の攻撃音
	EnemyManager* m_Enemymanager;//エネミーマネージャーへの参照
	GameCamera* m_GameCamera;//ゲームカメラへの参照
	ModelRender m_ModelRender;//モデルレンダラー
	CharacterController m_CharacterController;//キャラクターコントローラー
	Vector3 m_Position;	//座標
	Vector3 m_MoveSpeed;//移動速度
	Vector3 m_TargetPosition; //移動目標座標
	Quaternion m_Rotation;//回転
	FontRender m_fontRender;//フォントレンダラー
	enum EnAnimaationClip {
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip m_animationClips[enAnimationClip_Num];
	nsAI::NaviMesh    m_NvmMesh;         //ナビメッシュ
	nsAI::Path        m_Path;            //パス(経路)
	nsAI::PathFinding m_PathFiding;      //経路探索
	bool              Isend;             //パスの終端に到達したかどうかのフラグ
	bool              m_Startflag = true;//スタートフラグ
	float Atkinterval;//攻撃間隔
	float m_Speed;    //移動速度
	float m_DetectionTime=0.0f;
	int m_Hp=0;       //体力
	int m_Maxhp=100;  //最大体力
	int m_Enemyatk;   //攻撃力
};

