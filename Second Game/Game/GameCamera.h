#pragma once

class Player;

class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	Player* m_Player = nullptr; // プレイヤーへのポインタ
	Vector3 m_toCameraPos;// カメラの位置
};

