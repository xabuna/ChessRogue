#ifndef _BOARD_H_
#define _BOARD_H_

#include "include.h"

class BoardController;

class Board
{
	//HWND m_hWnd;

	Sprite Boardimg;
	Sprite BoardBackimg;

	BoardController* board[BOARD_SIZE][BOARD_SIZE] = { nullptr };

public:
	Board();
	//Board(HWND hWnd);
	~Board();

	float x, y;	

	void Init();
	void Update();
	void Draw();

	//void WinInit();
};

extern Board board;
#endif