#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	//�w�i��ǂݍ���
	m_ModelRender.Init( "Assets/modelData/stage/sutarg_2.tkm");
	m_ModelRender.Update();
	m_PhysicsStaticObject.CreateFromModel(m_ModelRender.GetModel(), m_ModelRender.GetModel().GetWorldMatrix());//���f������ÓI�ȕ����I�u�W�F�N�g�𐶐�
}

BackGround::~BackGround()
{

}

void BackGround::Render(RenderContext& rc)
{
	m_ModelRender.Draw(rc);
}