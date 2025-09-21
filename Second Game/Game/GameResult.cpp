#include "stdafx.h"
#include "GameResult.h"
#include "GameTiter.h"

GameResult::GameResult()
{
	//�w�i�摜
	m_spriteRender.Init("Assets/sprite/GameResult_2.DDS", 1920.0f, 1080.0f);
}

GameResult::~GameResult()
{

}

bool GameResult::Start()
{
	return true;
}

void GameResult::Score(int score)
{
	float time = g_gameTime->GetFrameDeltaTime();
	int intTime = static_cast<int>(time); // �����_�ȉ���؂�̂�
	int Fiftytimes = 50;//50�{
	m_Score += intTime * Fiftytimes;//�X�R�A���Z	
}

void GameResult::Update()
{
	//I�{�^���Ń^�C�g���ւ�
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		//if (sound != nullptr)
		//{
		//	sound->Stop();
		//	sound = nullptr;
		//}
		//Result�ړ�
		NewGO<GameTiter>(0, "m_gametiter");
		DeleteGO(this); // �^�C�g����ʂ��폜
	}
}

void GameResult::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);

	wchar_t bu[129];
	m_fontRender.SetPosition({ -600.0f,300.0f,0.0f });
	//�\������F��ݒ肷��B
	m_fontRender.SetColor(g_vec4White);
	// �X�R�A���擾
	int Count = m_Score;
	// ���W�𕶎���ɕϊ�   �����\�L��%d
	swprintf(bu, 129, L"Score: %d", Count);
	// �e�L�X�g���Z�b�g
	m_fontRender.SetText(bu);
	// �t�H���g�`��
	m_fontRender.Draw(rc);
}
