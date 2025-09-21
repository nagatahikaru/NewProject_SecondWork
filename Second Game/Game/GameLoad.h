#pragma once

class Player;
class BackGround;
class Game;
class EnemyManager;
class BulletManager;

class GameLoad:public IGameObject
{
public:
	GameLoad();
	~GameLoad();
	bool Start();
	void Update();
	void LoadBre();
	void Render(RenderContext& rc);

	Game*          m_game;
	Player*        m_player = nullptr;       //�v���C���[
	BackGround*    m_backGround = nullptr;   //�w�i
	EnemyManager*  m_enemymanager = nullptr; //�G
	BulletManager* m_bulletmanager = nullptr;//�e��
	SpriteRender   m_spriteRender;
	SpriteRender   m_LoadBarSpriteRender;
	SpriteRender   m_unitySpriteRender;
	SpriteRender   m_unity1SpriteRender;

	float m_Loadtimer = 0.0f;//���[�h���Ԃ��v�����邽�߂̃^�C�}�[
	FontRender m_DrawFont; // �t�H���g�����_���[

	bool m_showUnity = false; // ���j�e�B�����̕\���t���O
	int m_Maxnewgocount = 0; // �ő吶����
	int m_newgocount = 0; // ���݂̐�����

};

