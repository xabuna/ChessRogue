#include "Piece.h"

Piece::Piece()	{}

Piece::Piece(Pieceinfo _pi, PieceXY _pxy, PiecePower _pp, bool alive)
	: pi(_pi), pxy(_pxy), pp(_pp), alive(alive) { }

Piece::Piece(Pieceinfo _pi)
	: pi(_pi), alive(true) {}

Piece::Piece(PiecePower _pp)
	: pp(_pp) {}

Piece::~Piece()	{}

Piece::Piece(const Piece& _piece)
{
	pi = _piece.pi;
	pp = _piece.pp;
	alive = _piece.alive;
}

Piece& Piece::operator=(const Piece& _piece)
{
	if (this != &_piece)
	{
		pi = _piece.pi;
		pp = _piece.pp;	
		alive = _piece.alive;	

	}

	return *this;
}

void Piece::Draw() { }

PieceType Piece::getType() const { return this-> pi.type; }
int Piece::getRow() const {	return this->pi.row; }
int Piece::getCol() const { return this->pi.col; }
int Piece::getOwner() const { return this->pi.owner; }
int Piece::getHP() const { return this->pp.hp; }
int Piece::getAP() const { return this->pp.ap; }
int Piece::getDamage() const { return this->pp.damage; }
int Piece::getEvade() const { return this->pp.evade; }


bool Piece::getAlive() const { return alive; }

void Piece::setPosition(int _row, int _col) {

	pi.col = _col;
	pi.row = _row;

	pxy.x = (float)(BOARDSTART_X + (_col * TILE));
	pxy.y = (float)(BOARDSTART_Y + (_row * TILE));
}

