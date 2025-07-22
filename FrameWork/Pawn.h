#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.h"

class Pawn :public Piece
{
	Sprite Pawn_whimg;
	Sprite Pawn_bkimg;

public:
	Pawn();
	Pawn(Pieceinfo _pi, PieceXY _pxy, PiecePower _pp, bool alive = true);
	Pawn(Pieceinfo _pi);
	Pawn(PiecePower _pp);
	~Pawn();

	Pawn(const Pawn& _pawn);
	Pawn& operator=(const Pawn& _pawn);

	vector<pair<int, int>> getLegalMoves(BoardController* board) override;

	void Init();
	virtual void Draw();
	void Update();
};

#endif