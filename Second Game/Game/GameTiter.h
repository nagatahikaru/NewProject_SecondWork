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

	

	SpriteRender m_spriteRender;//Titer描写
	FontRender   m_fontRender;//タイトル文字
	float        m_alphas = 0.0f;//透明度変数
	bool         m_fadeIns = false;//切り替わりフラグ
};

