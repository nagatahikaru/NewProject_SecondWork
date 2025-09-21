#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
GameCamera::GameCamera()
{
}
GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{
	// �J�����̏���������
	m_toCameraPos.Set(0.0f, 0.0f, -1.0f);
	// �v���C���[�̃I�u�W�F�N�g���擾
	m_Player = FindGO<Player>("m_Player");

	//
	g_camera3D->SetNear(1.0f); // �J�����̋߂��̃N���b�s���O��
	g_camera3D->SetFar(100000.0f); // �J�����̉����̃N���b�s���O��
	return true;
}
void GameCamera::Update()
{
	if (m_Player == nullptr)
	{
		return; // �v���C���[��������Ȃ��ꍇ�͉������Ȃ�
	}
	//�J�����̍X�V
	//�����_���X�V
	Vector3 target = m_Player->m_Position;
	//�v���C���[�̑������炿����Ə�ɒ����_��ݒ�
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_toCameraPos;// ���݂̃J�����ʒu
	//�p�b�h�̓��͂��擾
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y���̉�]���v�Z
	Quaternion qRot;// ��]��\���N�H�[�^�j�I��
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x); // ���X�e�B�b�N��X�����͂�Y����]
	qRot.Apply(m_toCameraPos); // �J�����ʒu�ɉ�]��K�p
	//X���̉�]���v�Z
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos); // ���X�e�B�b�N��Y�����͂�X����]
	axisX.Normalize(); // ���K��
	qRot.SetRotationDeg(axisX, 1.3f * y); // X���̉�]��ݒ�
	qRot.Apply(m_toCameraPos); // �J�����ʒu�ɉ�]��K�p
	//�J�����̉�]�̏�����`�F�b�N����
	//�����_���王�_�܂ł̃x�N�g���𐧎~������
	//���K������ƁA�x�N�g���̑傫����1�ɂȂ�
	//�傫����1�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�����݂̂̏��ƂȂ�Ƃ�������
	Vector3 toPosDir = m_toCameraPos;// �����_����J�����ʒu�܂ł̃x�N�g��
	toPosDir.Normalize();// ���K��
	if (toPosDir.y < -0.2f)//Y����]�̏��
	{
		m_toCameraPos = toCameraPosOld;// ��]��K�p���Ȃ�
	}
	else if (toPosDir.y > 0.9f)
	{
		m_toCameraPos = toCameraPosOld; // ��]��K�p���Ȃ�
	}
	//���_���v�Z����
	Vector3 Pos = target + m_toCameraPos; // �����_�ɃJ�����ʒu�����Z���Ď��_���v�Z
	//
	g_camera3D->SetTarget(target); // �J�����̒����_��ݒ�
	g_camera3D->SetPosition(Pos); // �J�����̈ʒu��ݒ�
	g_camera3D->Update(); // �J�����̍X�V
}
