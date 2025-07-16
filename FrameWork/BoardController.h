#ifndef _BOARDCONTROLLER_H_
#define _BOARDCONTROLLER_H_

#include "include.h"
#include "Piece.h"

class Piece;

class BoardController {
private:


public:

	Piece* board[BOARD_SIZE][BOARD_SIZE];

	BoardController();
	~BoardController();

	void SetPiecesStarting();	//기물 기본 위치
	void Init();
	void Draw();

	Piece* getPiece(int row, int col) const;
	void setPiece(int row, int col, Piece* piece);
};

extern BoardController boardctrl;
#endif
