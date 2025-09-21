#include "stdafx.h"
#include "GameOver.h"
#include "GameResult.h"
#include "SoundManager.h"

GameOver::GameOver()
{

	
}

GameOver::~GameOver()
{

}

bool GameOver::Start()
{
	//�X�v���C�g�����_���[������
	m_spriteRender.Init("Assets/sprite/GameOver_2.DDS", 1980.0f, 1080.0f);
	SoundManager* soundManager = FindGO<SoundManager>("soundManager");       //
	m_GameOverBGM = soundManager->PlayingSound(Sound::enSound_OverBGM, true, 1.0f);//�Q�[���I�[�o�[BGM�Đ�
	return true;
}

void GameOver::Update()
{
	//L�{�^���Ń��U���g��
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		if (m_GameOverBGM != nullptr)
		{
			m_GameOverBGM->Stop();
			m_GameOverBGM = nullptr;
		}
		//Result�ړ�
		NewGO<GameResult>(0, "m_gameresult");
		DeleteGO(this); // �^�C�g����ʂ��폜
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}