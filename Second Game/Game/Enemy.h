#pragma once
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"
#include <random>
#include "SoundManager.h"

class Player;
class Bullet;
class EnemyManager;
class GameCamera;

class Enemy:public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start();
	/*void Startset();*/
	void Update();
	void Atk();
	void Move();
	void Rotation();
	void PlayAnimation();
	void Dead();	
	void Render(RenderContext& rc);

	Player* m_Player;//�v���C���[�ւ̎Q��
	Bullet* m_Bullet;//�e�ۂւ̎Q��
	SoundSource* m_GameATKSE = nullptr; //�G�̍U����
	EnemyManager* m_Enemymanager;//�G�l�~�[�}�l�[�W���[�ւ̎Q��
	GameCamera* m_GameCamera;//�Q�[���J�����ւ̎Q��
	ModelRender m_ModelRender;//���f�������_���[
	CharacterController m_CharacterController;//�L�����N�^�[�R���g���[���[
	Vector3 m_Position;	//���W
	Vector3 m_MoveSpeed;//�ړ����x
	Vector3 m_TargetPosition; //�ړ��ڕW���W
	Quaternion m_Rotation;//��]
	FontRender m_fontRender;//�t�H���g�����_���[
	enum EnAnimaationClip {
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip m_animationClips[enAnimationClip_Num];
	nsAI::NaviMesh    m_NvmMesh;         //�i�r���b�V��
	nsAI::Path        m_Path;            //�p�X(�o�H)
	nsAI::PathFinding m_PathFiding;      //�o�H�T��
	bool              Isend;             //�p�X�̏I�[�ɓ��B�������ǂ����̃t���O
	bool              m_Startflag = true;//�X�^�[�g�t���O
	float Atkinterval;//�U���Ԋu
	float m_Speed;    //�ړ����x
	float m_DetectionTime=0.0f;
	int m_Hp=0;       //�̗�
	int m_Maxhp=100;  //�ő�̗�
	int m_Enemyatk;   //�U����
};

