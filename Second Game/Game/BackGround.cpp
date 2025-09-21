#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	//背景を読み込む
	m_ModelRender.Init( "Assets/modelData/stage/sutarg_2.tkm");
	m_ModelRender.Update();
	m_PhysicsStaticObject.CreateFromModel(m_ModelRender.GetModel(), m_ModelRender.GetModel().GetWorldMatrix());//モデルから静的な物理オブジェクトを生成
}

BackGround::~BackGround()
{

}

void BackGround::Render(RenderContext& rc)
{
	m_ModelRender.Draw(rc);
}