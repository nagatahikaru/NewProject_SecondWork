#pragma once

class Player;

class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	Player* m_Player = nullptr; // �v���C���[�ւ̃|�C���^
	Vector3 m_toCameraPos;// �J�����̈ʒu
};

