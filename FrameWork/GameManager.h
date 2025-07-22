#pragma once
#include "Include.h"
struct SysTem
{
	int m_Save1;
	int m_Save2;

};

class GameManager
{
	Sprite Menuimg[2];

public:
	GameManager(void);
	~GameManager(void);

	FILE *fp;			//������ ����Ű�� ��ü �����͸� ����
	SysTem m_SysTem;	//�ý��ۿ� �����Ѵ�.

	bool m_Pause;
	int m_GameSpeed;
	
	DWORD GameTime;
	bool m_GameStart;

	bool m_Collision;

	std::list<Player2*>	myList;
	bool Respawn;


	void GameReset(void);
	void Init();
	void Update();
	void Draw();
	void Save();
	void Delete();

	// /////////////////////////////////////
	// bool pieceSelected = false; // �⹰ ����
	// int selectedRow = -1; // ������ �⹰ ��
	// int selectedCol = -1; // ������ �⹰ ��
	// /////////////////////////////////////
	
	
};

extern GameManager Gmanager;

