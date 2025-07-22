#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "Piece.h"

class Bishop :public Piece
{
	Sprite Bishop_whimg;
	Sprite Bishop_bkimg;
public:
	Bishop();
	Bishop(Pieceinfo _pi, PieceXY _pxy, PiecePower _pp, bool alive = true);
	Bishop(Pieceinfo _pi);
	Bishop(PiecePower _pp);
	~Bishop();

	Bishop(const Bishop& _bishop);
	Bishop& operator=(const Bishop& _bishop);

	vector<pair<int, int>> getLegalMoves(BoardController* boardctrl) override;

	void Init();
	virtual void Draw();
	void Update();
};

#endif