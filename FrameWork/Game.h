#ifndef __Game_H__
#define __Game_H__

#include "Include.h"

enum class GamePhase { 
	BOARD = 0, 
	MOVE_CAMERA = 1, 
	BATTLE = 2, 
	GAME_OVER = 3, 
	MAIN = 4, 
	TRANSITION = 5,
	GAMEOVER = 6,
	NONE = 100  
};


class Game : public Chap
{
    HDC m_hdc;
	HWND m_hWnd;
	DWORD transitionEndTime = 0;

	bool transitionStarted = false;
public:

	Game();
	~Game();

	GamePhase gamephase;
	GamePhase prevPhase = GamePhase::MAIN;
	////////////////////////////////////////////////
	static Game* instance;// 정적 인스턴스 포인터
	static Game* getInstance();// 인스턴스 접근자

	bool battleStarted = OFF;

	DWORD GameTime;

	virtual void Init(HWND m_hWnd);
	virtual void Update(double frame);
	virtual void Draw(HDC hdc);

	virtual void OnMessage(MSG* msg);

	void SetWindowHandle(HWND hWnd) { m_hWnd = hWnd; }

	GamePhase getGamePhase() { return gamephase; }

	RECT btn_battle[3] = {
		{    0, 832,  580, 1050 },			// Attack
		{ 1100, 832, 1680, 1050 },			// UseItem
		{  655, 832, 1025, 1050 }			// Defence
	};

	RECT attack_box, useitem_box, defence_box;


    void SetHDC(HDC hdc);
    HDC GetHDC();
};

#endif