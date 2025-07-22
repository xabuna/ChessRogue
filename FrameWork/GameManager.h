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

	FILE *fp;			//파일을 가리키는 객체 포인터를 만들어서
	SysTem m_SysTem;	//시스템에 저장한다.

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
	// bool pieceSelected = false; // 기물 선택
	// int selectedRow = -1; // 선택한 기물 행
	// int selectedCol = -1; // 선택한 기물 열
	// /////////////////////////////////////
	
	
};

extern GameManager Gmanager;

