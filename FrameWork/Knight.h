#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "Piece.h"

class Knight :public Piece
{
	Sprite Knight_whimg;
	Sprite Knight_bkimg;

public:
	Knight();
	Knight(Pieceinfo _pi, PieceXY _pxy, PiecePower _pp, bool alive = true);
	Knight(Pieceinfo _pi);
	Knight(PiecePower _pp);
	~Knight();

	Knight(const Knight& _knight);
	Knight& operator=(const Knight& _knight);

	vector<pair<int, int>> getLegalMoves(BoardController* boardctrl) override;

	void Init();
	virtual void Draw();
	void Update();
};

#endif