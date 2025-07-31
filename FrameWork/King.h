#ifndef _KING_H_
#define _KING_H_

#include "Piece.h"

class King :public Piece
{
	Sprite King_whimg;
	Sprite King_bkimg;

public:
	King();
	King(Pieceinfo _pi, PieceXY _pxy, PiecePower _pp, bool alive = true);
	King(Pieceinfo _pi);
	King(PiecePower _pp);

	~King();

	King(const King& _king);
	King& operator=(const King& _king);

	vector<pair<int, int>> getLegalMoves(BoardController* board) override;

	void Init();
	virtual void Draw();
	void Update();
};

#endif