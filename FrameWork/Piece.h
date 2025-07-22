#ifndef _PIECE_H_
#define _PIECE_H_

#include "Include.h"

using namespace std;

struct Pieceinfo
{
	int row;
	int col;
	int owner = PLAYER;
	PieceType type;
};

struct PieceXY
{
	float x;
	float y;
};

struct PiecePower
{
	int hp;
	int ap;
	int damage;
	int evade;
};

class BoardController;

class Piece
{
protected:

	Pieceinfo pi;
	PieceXY pxy;
	PiecePower pp;

	bool alive;
	
	HWND m_hWnd = nullptr;
	HDC m_hdc = nullptr;

public:
	Piece();
	Piece(Pieceinfo _pi, PieceXY _pxy, PiecePower _pp, bool alive = ALIVE);
	Piece(Pieceinfo _pi);
	Piece(PiecePower _pp);
	virtual ~Piece();
	Piece(const Piece& _piece);
	Piece& operator=(const Piece& _piece);
	
	virtual void Draw();
	virtual vector<pair<int, int>> getLegalMoves(BoardController* boardCtrl) = 0;

	// 百百百百百百
	int getOwner() const;
	int getRow() const;
	int getCol() const;

	int getHP() const; 
	int getAP() const;
	int getDamage() const;
	int getEvade() const;

	bool getAlive() const;
	PieceType getType() const;

	// 济悸悸技技悸技济
	int setHP() const;
	int setAP() const;
	int setDamage() const;
	
	
	void setPosition(int _row, int _col);
};


#endif