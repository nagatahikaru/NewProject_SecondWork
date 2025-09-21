#include "stdafx.h"
#include "Game.h"
#include "GameOver.h"
#include "GameClear.h"
#include "GameCamera.h"
#include "GameLoad.h"
#include "Player.h"
#include "BackGround.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "SoundManager.h"

Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_Player);
	DeleteGO(m_BackGround);
	DeleteGO(m_GameCamera);
	DeleteGO(m_Enemymanager);
	DeleteGO(m_Bulletmanager);
}

bool Game::Start()
{		
	m_GameCamera=NewGO<GameCamera>(0, "m_GameCamera");//�Q�[���J��������
	SkyCube* sky = NewGO<SkyCube>(0);                // �X�J�C�N���X�̃C���X�^���X�𐶐�
	sky->SetLuminance(0.2f);                         // �X�J�C�̋P�x��ݒ�
	sky->SetScale(10000.0f);                       // �X�J�C�̃X�P�[����ݒ�
	sky->SetType(enSkyCubeType_NightToon_2);         // �X�J�C�̃^�C�v��ݒ�
	g_renderingEngine->DisableTonemap();             // �g�[���}�b�s���O�𖳌��ɂ���
	m_Player = FindGO<Player>("m_Player");
	m_Time = 120; // �������Ԃ�60�b�ɐݒ�
	SoundManager* soundManager = FindGO<SoundManager>("soundManager");       //
	m_GameBGM = soundManager->PlayingSound(Sound::enSound_InGameBGM, true, 1.0f);//
	return true;
}

void Game::Update()
{
	if (m_Player == nullptr)return;

	m_Time -= g_gameTime->GetFrameDeltaTime();
	//�v���C���[�̗̑͂�0�ȉ��ŃQ�[���I�[�o�[
	
    if (m_Player->m_PlayreHp<=0)
	{
		if (m_GameBGM != nullptr)
		{
			m_GameBGM->Stop();
			m_GameBGM = nullptr;
		}
		//�Q�[���I��
		NewGO<GameOver>(0, "m_Gameover");
		DeleteGO(this); // �Q�[����ʂ��폜
	}
	//���Ԑ؂�ŃQ�[���N���A
	if (m_Time <= 0)
	{
		if (m_GameBGM != nullptr)
		{
			m_GameBGM->Stop();
			m_GameBGM = nullptr;
		}
		NewGO<GameClear>(0, "m_Gameclear");
		DeleteGO(this);
	}
}

void Game::Render(RenderContext& rc)
{
	
	// �`�悷�镶�����p��
	wchar_t bu[129];
	m_fontRender.SetPosition({ -600.0f,150.0f,0.0f });
	//�\������F��ݒ肷��B
	m_fontRender.SetColor(g_vec4White);
	// �G�l�~�[�̍��W���擾
	int Time = m_Time;
	// ���W�𕶎���ɕϊ�   
	swprintf(bu, 129, L"Time: %d",Time);
	// �e�L�X�g���Z�b�g
	m_fontRender.SetText(bu);
	// �t�H���g�`��
	m_fontRender.Draw(rc);
}