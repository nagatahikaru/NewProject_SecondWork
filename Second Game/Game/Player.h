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
	float m_Atktime = 0.0f;//çUåÇä‘äu
	float m_Time; //åoâﬂéûä‘
	float SpeedBaika = 2.0f; //ë¨ìxî{ó¶
	float m_TimeLimit = 5.0f; //êßå¿éûä‘
	float m_ReloadTime = 0.0f; //ÉäÉçÅ[Éhéûä‘
	FontRender m_fontRender;

};

