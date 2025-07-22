#ifndef _ROOK_H_
#define _ROOK_H_

#include "Piece.h"


class Rook :public Piece
{
	Sprite Rook_whimg;
	Sprite Rook_bkimg;

public:
	Rook();

	Rook(Pieceinfo _pi, PieceXY _pxy, PiecePower _pp, bool alive = true);

	Rook(Pieceinfo _pi);

	Rook(PiecePower _pp);

	~Rook();

	Rook(const Rook& _rook);
	Rook& operator=(const Rook& _rook);

	vector<pair<int, int>> getLegalMoves(BoardController* boardCtrl) override;

	void Init();
	virtual void Draw();
	void Update();
};


#endif