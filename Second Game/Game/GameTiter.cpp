#include "stdafx.h"
#include "GameTiter.h"
#include "GameLoad.h"
#include "SoundManager.h"

GameTiter::GameTiter()
{
	//Titer�̃t�@�C���p�X
	m_spriteRender.Init("Assets/sprite/GameTiter_2.DDS",1920.0f,1080.0f);
	m_fontRender.SetText(L"�Q�[���X�^�[�g\n""  (J�L�[)");
	m_fontRender.SetPosition({ 100.0f,100.0f,0.0f });
	m_fontRender.SetScale(2.0f);
	m_fontRender.SetColor({ m_alphas,0.0f,0.0f,m_alphas });
}

GameTiter::~GameTiter()
{

}

bool GameTiter::Start()
{
	//�^�C�g��BGM�Đ�
	SoundManager* soundManager = FindGO<SoundManager>("soundManager");       //
	m_GameTiterBGM = soundManager->PlayingSound(Sound::enSound_ClearBGM, true, 1.0f);//
	return true;
}

void GameTiter::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (m_GameTiterBGM != nullptr)
		{
			m_GameTiterBGM->Stop();
			m_GameTiterBGM = nullptr;
		}
		//�Q�[���J�n
		NewGO<GameLoad>(0, "m_gameload");		
		DeleteGO(this); // �^�C�g����ʂ��폜
	}
	Font();
}

void GameTiter::Font()
{
	const float fadeSpeed = 0.01f;

	if (m_fadeIns)
	{
		// �t�F�[�h�C�� �� �A���t�@�����i�\���ցj
		m_alphas += fadeSpeed;
		if (m_alphas >= 1.0f)
		{
			m_alphas = 1.0f;
			m_fadeIns = false; // ���̓t�F�[�h�A�E�g��
		}
	}
	else
	{
		// �t�F�[�h�A�E�g �� �A���t�@�����i�����ցj
		m_alphas -= fadeSpeed;
		if (m_alphas <= 0.00f)
		{
			m_alphas = 0.00f;
			m_fadeIns = true; // ���̓t�F�[�h�C����
		}
	}
	m_fontRender.SetColor({ m_alphas, 0, 0, m_alphas });    // �^�C�g���e�L�X�g�̓����x���X�V
}

void GameTiter::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}
