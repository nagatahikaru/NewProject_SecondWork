#pragma once

class Player;
class GameCamera;
class BackGround;
class GameClear;
class GameOver;
class GameLoad;
class Enemy;
class Bullet;
class EnemyManager;
class BulletManager;


//Game�V�[�����Ǘ�����N���X�B
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	//�X�V����
	void Update();
	void Render(RenderContext& rc);



	// "*"�����鎞��->�Ł@����ȊO�̎���"."��"*"���g��Ȃ�
	Player*        m_Player= nullptr;        //�v���C���[
	BackGround*    m_BackGround = nullptr;   //�w�i
	EnemyManager*  m_Enemymanager = nullptr; //�G
	BulletManager* m_Bulletmanager = nullptr;//�e��
	GameCamera*    m_GameCamera= nullptr;    //�Q�[���J����
	GameLoad*      m_GameLoad = nullptr;     //���[�h���
	SoundSource*   m_GameBGM = nullptr;      //�Q�[������BGM
	GameClear*     m_Gameclear = nullptr;    //�Q�[���J����
	GameOver*      m_GameOver = nullptr;     //�Q�[���I�[�o�[
	FontRender        m_fontRender;                //�t�H���g
	bool exists = false;//�����t���O
	float m_Time= 0.0f;//����
	
	
};

