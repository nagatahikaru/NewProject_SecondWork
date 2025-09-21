#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "EnemyManager.h"
#include "GameCamera.h"
#include <random>

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

bool Enemy::Start()
{
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);

	m_ModelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips,enModelUpAxisY);
	//�i�r���b�V�����\�z�B
	m_NvmMesh.Init("Assets/nvm/Nvm_2.tkn");
	// �����G���W���̏�����
	// ���s���ƂɈقȂ闐����𐶐����邽�߁Astd::random_device���g�p
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	// �͈� [0.0, 100.0) ��float�̗����𐶐����镪�z���`
	std::uniform_real_distribution<float> dist(100.0f, 10000.0f);
	float x = dist(engine);// x���W�̗���
	float z = dist(engine);// z���W�̗���
	m_ModelRender.SetShadowCasterFlag(false);
	m_Position = Vector3{ x,0.0f,z };
	m_ModelRender.SetPosition(m_Position);
	m_CharacterController.Init(25.0f, 75.0f, m_Position);
	m_CharacterController.GetRigidBody();
	m_Player = FindGO<Player>("m_Player");
	m_GameCamera = FindGO<GameCamera>("m_GameCamera");
	SoundManager* soundManager = FindGO<SoundManager>("soundManager");       //
	m_GameATKSE = soundManager->PlayingSound(Sound::enSound_DamageSE, false, 1.0f);//�G�̍U����
	return true;
}

void Enemy::Update()
{
	Move();
	Rotation();	
	Dead();	
}

void Enemy::Atk()
{
	if (m_Player == nullptr) return;
	m_GameATKSE->Play(false); //�G�̍U�����Đ�
	m_Enemyatk = rand() % 20 + 5;  //�U���͂������_���ɐݒ�(5~25)
	//�v���C���[�̗̑͂����炷
	m_Player->m_PlayreHp -= m_Enemyatk;

}

void Enemy::Move()
{
	
	Vector3 pos = m_Player->m_Position; //�v���C���[�̈ʒu
	Vector3 Distance = m_Position - pos;//�v���C���[�Ƃ̋���
	float dist = Distance.Length();	
	PlayAnimation();

	////�U��
	Atkinterval = Atkinterval + g_gameTime->GetFrameDeltaTime();
	if (dist <= 30.0f && Atkinterval == 0.5f)
	{		
		Atk();
		Atkinterval = 0.0f;		
		return;
	}
	if (Atkinterval > 0.5f)
	{
		Atkinterval = 0.2f;
	}

	if (dist >= 950.0f)
	{
		m_DetectionTime += g_gameTime->GetFrameDeltaTime();
		//�v���C���[��ǂ�������
		if(m_DetectionTime<=1.0f)
		{
			m_TargetPosition = pos;
			m_DetectionTime = 0.0f;
		}
		
		//�p�X�T��
		m_PathFiding.Execute(
			m_Path,                     //�\�z���ꂽ�o�X�̊i�[��
			m_NvmMesh,                  //�i�r���b�V��
			m_Position,                 //�J�n���W
			m_TargetPosition,           //�ړ��ڕW���W				
			PhysicsWorld::GetInstance(),//�����G���W��
			50.0f,                      //AI�G�[�W�F���g�̔��a
			200.0f                      //AI�G�[�W�F���g�̍���
		);
		//�ړ����x�̐ݒ�		
		m_Speed = 10.5f;//�ړ����x�������ɂ���ĕύX		

		//�p�X�̏���ړ�����
		m_Position = m_Path.Move(
			m_Position, //�J�n���W
			m_Speed,    //�ړ����x
			Isend       //�p�X�I�_
		);
	}
	if(dist <=1000.0f)
	{
		m_Speed = 1.0f;//�ړ����x�������ɂ���ĕύX
		Distance.Normalize();
		 m_Position += Distance* m_Speed * g_gameTime->GetFrameDeltaTime();
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
		if(m_MoveSpeed.y < -100.0f)
		{
			Dead();
		}
	}
	PlayAnimation();
	//�G�l�~�[�̈ʒu�X�V
	m_ModelRender.SetPosition(m_Position);
	Rotation();
	//�G�l�~�[�̍X�V
	m_ModelRender.Update();
}

void Enemy::Rotation()
{
	if (m_Player == nullptr) return;
	Vector3 toPlayer = m_Player->GetPosition() - m_Position;
	toPlayer.Normalize();
	m_Rotation.SetRotationYFromDirectionXZ(toPlayer);// Y�����̉�]��ݒ�
	m_ModelRender.SetRotation(m_Rotation);
}

void Enemy::PlayAnimation()
{
	m_ModelRender.PlayAnimation(enAnimationClip_Run);
	//�A�j���[�V�����𑝂₷�p�̃X�y�[�X
}

void Enemy::Dead()
{	
	if(m_Position.y<-100.0f)
	{
		Deactivate();
		return;
	}
	auto bullet = FindGO<Bullet>("bullet");
	Vector3 dif=bullet->m_Position - m_Position;
	float dist = dif.Length();
	if(dist<=50.0f)
	{
		bullet->Atk();
		; //�e�ۂ̍U���͕��̗͂����炷
		if (m_Hp <= 0)
		{
			m_isActive = false;
			m_Player->m_Score += 100; //�X�R�A���Z
			Deactivate();
		}
	}
}

void Enemy::Render(RenderContext& rc)
{
	if (!m_isActive) return; // ��A�N�e�B�u�Ȃ�`��X�L�b�v

	// ���f���̕`�揈��

	m_ModelRender.Draw(rc); // ���f����`��	

//	wchar_t bu[129];
//m_fontRender.SetPosition({ -600.0f,150.0f,0.0f });
////�\������F��ݒ肷��B
//m_fontRender.SetColor(g_vec4White);
//// �G�l�~�[�̍��W���擾
//int EnemyCount = m_Enemymanager->m_EnemyCount;
//// ���W�𕶎���ɕϊ�   
//swprintf(bu, 129, L"EnemyCount: EnemyCount=%1", EnemyCount);
//// �e�L�X�g���Z�b�g
//m_fontRender.SetText(bu);
//// �t�H���g�`��
//m_fontRender.Draw(rc);
}
