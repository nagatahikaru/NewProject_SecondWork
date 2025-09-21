#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "GameCamera.h"
#include "GameResult.h"

Player::Player()
{
	
}

Player::~Player()
{

}

bool Player::Start()
{
	//�A�j���[�V�����N���b�v�����[�h����B
	m_AnimationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_AnimationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_ModelRender.Init("Assets/modelData/unityChan.tkm", m_AnimationClips, enAnimationClip_Num, enModelUpAxisY);
	m_ModelRender.SetShadowCasterFlag(false);
	m_Position = Vector3{ 200.0f,0.0f,50.0f };
	m_ModelRender.SetPosition(m_Position);
	m_CharacterController.Init(25.0f, 75.0f, m_Position);
	m_Bulletmanager = FindGO<BulletManager>("bulletmanager");
	
	m_BulletCount = 6; //�e�ۂ̏�����
	m_PlayreHp = 100;
	return true;
}

void Player::Update()
{
	m_GameCamera = FindGO<GameCamera>("m_GameCamera");
	if(m_GameCamera ==nullptr)
	{
		return;
	}
	Rotation();	
	ATK();
	Score();
	Move();
}

void Player::Move()
{
	//xz�̈ړ����x��0.0f�ɂ���
	m_MoveSpeed.x = 0.0f;
	m_MoveSpeed.z = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ��擾
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���������ė���B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//�������ɂ͈ړ������Ȃ�
	forward.y = 0.0f;
	right.y = 0.0;

	//���X�e�B�b�N�̓��͗ʂ�200.0f����Z
	right *= stickL.x * 200.0f;
	forward *= stickL.y * 200.0f;

	//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����B
	m_MoveSpeed += right + forward;

	//B�{�^����������Ă���Ԃ͈ړ����x��2�{�ɂ���
	if (g_pad[0]->IsPress(enButtonB) && m_Time <= m_TimeLimit)
	{
		m_MoveSpeed.x *= SpeedBaika; // B�{�^����������Ă���Ԃ͉E�����̑��x��2�{�ɂ���
		m_MoveSpeed.z *= SpeedBaika; // B�{�^����������Ă���Ԃ͑O�����̑��x��2�{�ɂ���
		m_Time = m_Time + g_gameTime->GetFrameDeltaTime(); // �o�ߎ��Ԃ��X�V
	}
	else
	{
		//�o�ߎ��Ԃ����Z���Ă���
		m_Time = m_Time - g_gameTime->GetFrameDeltaTime();
	}
	if (m_Time < 0.0f) // �o�ߎ��Ԃ�0�ȉ��ɂȂ�����
	{
		m_Time = 0.0f; // �o�ߎ��Ԃ�0�Ƀ��Z�b�g
	}

	//�n�ʂɂ��Ă�����
	if (m_CharacterController.IsOnGround())
	{
		//�d�͂��Ȃ���
		m_MoveSpeed.y = 0.0f;
	}
	else//�n�ʂɂ��Ă��Ȃ�������
	{
		//�d�͂𔭐�������
		const float gravety = 25.5f;//�d�͂̒萔
		m_MoveSpeed.y -= gravety;
	}
	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������
	m_Position = m_CharacterController.Execute(m_MoveSpeed, g_gameTime->GetFrameDeltaTime());
}

void Player::ATK()
{
	m_Bulletmanager = FindGO<BulletManager>("m_bulletManager");
	if (!m_Bulletmanager) {
		printf("BulletManager �� nullptr �ł��I\n");
	}

	//�N�[���^�C��
	if (m_Atktime > 0) {
		m_Atktime -= g_gameTime->GetFrameDeltaTime();
		if (m_Atktime < 0) m_Atktime = 0;
	}

	//�U������,L�X�e�B�b�N�������݂Œe�۔���
	if (g_pad[0]->IsTrigger(enButtonX)&& m_BulletCount>0)
	{
		if(m_Atktime<=0)		
		{
			// �v���C���[�̌����i�O�����x�N�g���j
			Vector3 dir(0, 0, 1);      // Z+��������̑O�����ɂ���
			Quaternion rot = m_Rotation;
			rot.Apply(dir);
			dir.Normalize(); // �O�̂��ߐ��K��

            // �v���C���[�̈ʒu�i�����O�ɂ��炷�Ǝ��R�j
            Vector3 pos = m_Position + dir * 10.0f + Vector3(0, 10.0f, 0);

            // ���˖���
			m_Bulletmanager->FireBullet(pos, dir);
			m_BulletCount--;
			m_Atktime = 0.5;
		}
	}

	//�e�ۂ̃����[�h���Ԃƒe�ۂ̕�[
	//J�{�^���𒷉����Ń����[�h
	if (g_pad[0]->IsPress(enButtonA)&&m_BulletCount >= 0)
	{		
		//�����[�h�^�C��
		m_ReloadTime += g_gameTime->GetFrameDeltaTime();
	    if (m_ReloadTime >= 1 && m_BulletCount <6)
	    {
			int i = 6 - m_BulletCount;//��[����e�ۂ̐�
			m_BulletCount += i; //�e�ە�[
			auto bullet = FindGO<Bullet>("bullet");
			bullet->Reload();		  
			m_ReloadTime = 0;
	    }
	}
}

void Player::Rotation()
{
	//�J�����̑O�����������Ă���
	Vector3 forward = g_camera3D->GetForward();
	forward.y = 0;
	forward.Normalize();
	//�������Z�b�g
	m_Rotation.SetRotationYFromDirectionXZ(forward);
	//�G�`������ɉ�]��������
	m_ModelRender.SetRotation(m_Rotation);
	
}

void Player::Score()
{
	float time = g_gameTime->GetFrameDeltaTime();
	int intTime = static_cast<int>(time); // �����_�ȉ���؂�̂�
	int Fiftytimes = 50;//50�{
	//GameResult->m_Score += intTime * Fiftytimes;//�X�R�A���Z	
}

void Player::Render(RenderContext& rc)
{
	m_GameCamera = FindGO<GameCamera>("m_GameCamera");
	if (m_GameCamera == nullptr)
	{
		return;
	}
	wchar_t bu[129];
	m_fontRender.SetPosition({ -600.0f,300.0f,0.0f });
	//�\������F��ݒ肷��B
	m_fontRender.SetColor(g_vec4White);
	// �X�R�A���擾
	int Count = m_BulletCount;
	// ���W�𕶎���ɕϊ�   �����\�L��%d
	swprintf(bu, 129, L"�e��: %d",Count);
	// �e�L�X�g���Z�b�g
	m_fontRender.SetText(bu);
	// �t�H���g�`��
	m_fontRender.Draw(rc);

	// �e�l�܂�\��
	if (m_Bulletmanager && m_Bulletmanager->IsBulletStuck()) {
		m_fontRender.SetPosition({ -600.0f,400.0f,0.0f });
		m_fontRender.SetColor({ 1.0f, 0.0f, 0.0f, 1.0f }); // �ԐF
		m_fontRender.SetText(L"�e�l�܂�I");
		m_fontRender.Draw(rc);
	}
}

