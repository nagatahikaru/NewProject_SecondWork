#include "stdafx.h"
#include "GameLoad.h"
#include "Game.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "BackGround.h"
#include "Player.h"
#include "SoundManager.h"

GameLoad::GameLoad()
{

}

GameLoad::~GameLoad()
{

}

bool GameLoad::Start()
{

	m_spriteRender.Init("Assets/sprite/GameLoad_2.DDS", 1920.0f, 1080.0f);

	m_LoadBarSpriteRender.Init("Assets/sprite/Enemy.DDS", 100.0f, 150.0f);

	m_unitySpriteRender.Init("Assets/sprite/Sign_No.DDS", 200.0f, 200.0f);
	m_unitySpriteRender.SetPosition(Vector3(-50.0f, -125.0f, 0.0f));

	m_unity1SpriteRender.Init("Assets/sprite/Sign_Okay.DDS", 200.0f, 200.0f);
	m_unity1SpriteRender.SetPosition(Vector3(-50.0f, -125.0f, 0.0f));
	SoundManager* soundManager = FindGO<SoundManager>("soundManager");       //
	m_GameLoadBGM = soundManager->PlayingSound(Sound::enSound_LoadBGM, true, 1.0f);//
	NewGO<BackGround>(0, "m_BackGround");//�w�i����
	NewGO<Player>(0, "m_Player");//�v���C���[����
	NewGO<BulletManager>(0, "m_bulletManager");//6���̒e�ۂ𐶐�
	NewGO<EnemyManager>(0, "m_enemyManager");//20�̂̓G�𐶐�
	/*m_Maxnewgocount = 26;
	m_newgocount = 0;*/
	return true;
}

void GameLoad::Update()
{

	
	// �����Ƀ��[�h����������
	m_Loadtimer += g_gameTime->GetFrameDeltaTime();
	
	int unityFrame = (int)(m_Loadtimer * 3) % 2; // 0�܂���1�����݂ɐ؂�ւ���
	if (unityFrame == 0)
	{
		m_showUnity = true; // ���j�e�B�����̕\���t���O��true�ɐݒ�
	}
	else
	{
		m_showUnity = false; // ���j�e�B�����̕\���t���O��false�ɐݒ�
	}

	//���Ԍo�߂Ń��[�h�o�[��L�΂��B
	float scale = 1.0f + m_Loadtimer * 1.534;
	if (scale > 15.0f) scale = 15.0f; // �ő�15�{�܂�
	//�X�v���C�g��������E�ɐL�т�悤��X�̈ʒu��␳����
	float wide = 100.0f * scale;
	//�X�v���C�g�̑傫���ƈʒu��ݒ�
	m_LoadBarSpriteRender.SetScale(Vector3(scale, 1.15f, 1.0f));
	//�X�v���C�g�̒��S����ʒ����ɂȂ�悤�Ɉʒu�𒲐�
	m_LoadBarSpriteRender.SetPosition(Vector3(-815.0f + wide / 2.0f, -292.0f, 0.0f));

	if (m_Loadtimer > 15)
	{
		if (m_GameLoadBGM != nullptr)
		{
			m_GameLoadBGM->Stop();
			m_GameLoadBGM = nullptr;
		}
		// ���[�h������������Q�[�����J�n
		NewGO<Game>(0, "m_game");
		DeleteGO(this);
		return;
	}
	LoadBre();
	m_LoadBarSpriteRender.Update();
}

void GameLoad::LoadBre()
{	
	//wchar_t text[129];
	//if (m_Loadtimer < 4) {
	//	swprintf_s(text, _countof(text), L"���j�e�B�����ړ���.");
	//}
	//else if (m_Loadtimer < 6) {
	//	swprintf_s(text, _countof(text), L"���j�e�B�����ړ���..");
	//}
	//else if (m_Loadtimer < 8) {
	//	swprintf_s(text, _countof(text), L"���j�e�B�����ړ���...");
	//}
	//m_DrawFont.SetText(text);// �t�H���g�̃e�L�X�g��ݒ�
	//m_DrawFont.SetPosition({ -400.0f, -400.0f, 100.0f });// �t�H���g�̈ʒu��ݒ�
	//m_DrawFont.SetScale(1.5f);// �t�H���g�̑傫����ݒ�
	//m_DrawFont.SetColor(g_vec4White);// �t�H���g�̐F��ݒ�
	//m_unitySpriteRender.Update();// ���j�e�B�����̃X�v���C�g���X�V
	//m_unity1SpriteRender.Update();// ���j�e�B�����̃X�v���C�g���X�V
}

void GameLoad::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_LoadBarSpriteRender.Draw(rc);
	if (m_showUnity == true)
	{
		m_unitySpriteRender.Draw(rc);
	}
	else
	{
		m_unity1SpriteRender.Draw(rc);
	}

	
	// �t�H���g�̕`��
	m_DrawFont.Draw(rc);
}