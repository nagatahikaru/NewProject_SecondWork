#pragma once

//背景。

class BackGround : public IGameObject
{
public:
    BackGround();
    ~BackGround();
    //描画関数。
    void Render(RenderContext& rc);
    //モデルレンダ―。     

    ModelRender m_ModelRender;
    PhysicsStaticObject m_PhysicsStaticObject;// 物理オブジェクト
};