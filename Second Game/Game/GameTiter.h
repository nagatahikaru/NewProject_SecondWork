#pragma once

class GameLoad;

class GameTiter:public IGameObject
{
public:
	GameTiter();
	~GameTiter();
	bool Start();
	void Update();
	void Font();
	void Render(RenderContext& rc);

	

	SpriteRender m_spriteRender;//Titer�`��
	FontRender   m_fontRender;//�^�C�g������
	float        m_alphas = 0.0f;//�����x�ϐ�
	bool         m_fadeIns = false;//�؂�ւ��t���O
};

