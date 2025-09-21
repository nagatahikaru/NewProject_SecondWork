#pragma once

class Bullet;
class Enemy;
class BulletManager;
class GameCamera;
class GameResult;

class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Move();
	void ATK();
	void Rotation();
	void Score();
	void Render(RenderContext& rc);

	Vector3 GetPosition()const
	{
		return m_Position;
	}
	
	std::vector<Enemy*> m_EnemyPool;
	std::vector<Bullet*> m_BulletPool;
	BulletManager* m_Bulletmanager;
	SoundSource* m_ShotSound = nullptr; //ショット音
	SoundSource* m_ReloadSound = nullptr; //リロード音
	GameResult* m_GameResult;
	GameCamera* m_GameCamera;
	ModelRender m_ModelRender;
	Vector3 m_Position;
	Vector3 m_MoveSpeed;
	CharacterController m_CharacterController;
	Quaternion m_Rotation;
	enum EnAnimaationClip {	
		enAnimationClip_Idle,
		enAnimationClip_Num,
	};
	AnimationClip m_AnimationClips[enAnimationClip_Num];
	int m_PlayreHp = 0;	
	int m_BulletCount = 6;
	int m_Score = 0;
	float m_Atktime = 0.0f;//攻撃間隔
	float m_Time; //経過時間
	float SpeedBaika = 2.0f; //速度倍率
	float m_TimeLimit = 5.0f; //制限時間
	float m_ReloadTime = 0.0f; //リロード時間
	FontRender m_fontRender;

};

