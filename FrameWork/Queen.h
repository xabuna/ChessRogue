#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "Piece.h"

class Queen :public Piece
{
	Sprite Queen_whimg;
	Sprite Queen_bkimg;

public:
	Queen();
	Queen(Pieceinfo _pi, PieceXY _pxy, PiecePower _pp, bool alive = true);
	Queen(Pieceinfo _pi);
	Queen(PiecePower _pp);
	~Queen();

	Queen(const Queen& _queen);
	Queen& operator=(const Queen& _queen);

	vector<pair<int, int>> getLegalMoves(BoardController* boardCrtl) override;

	void Init();
	virtual void Draw();
	void Update();
};

#endif