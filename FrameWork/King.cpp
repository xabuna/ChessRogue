#include "King.h"

King::King() {}

King::King(Pieceinfo _pi, PieceXY _pxy, PiecePower _pp, bool alive)
	: Piece(_pi, _pxy, _pp, alive) {
}

King::King(Pieceinfo _pi)
	: Piece(_pi) {
	Init();

	setPosition(_pi.row, _pi.col);
}
King::King(PiecePower _pp)
	: Piece(PiecePower{ 10, 1, 100, 30 }) {}

King::~King() {
	//딜리트 스프라이트
}

King::King(const King& _king)
	: Piece(_king) {
}

King& King::operator=(const King& _king) {
	if (this != &_king) {
		Piece::operator=(_king);
		//추가속성or기능
		//스프라이트 머시기
	}
	return *this;
}

vector<pair<int, int>> King::getLegalMoves(BoardController* boardctrl)
{
	vector<pair<int, int>>legalMoves;
	legalMoves.reserve(10);

	

	// 8방향 이동 
	int kingDirections[8][2] = {
		{-1, 0},   // ↑
		{1, 0},    // ↓
		{0, -1},   // ←
		{0, 1},    // →
		{-1, -1},  // ↖
		{-1,  1},  // ↗
		{ 1, -1},  // ↙
		{ 1,  1}   // ↘
	};

	int startRow{}; // 캐슬링
	int startColWH{}; // 캐슬링
	int startColBK{};

    if (pi.owner == PLAYER && pi.row == 6) {
        startRow = 7;
		startColWH = 5;
    }
    else if (pi.owner == AI && pi.row == 1) {
        startRow = 0;
		startColBK = 4;
	}

	int newRow;
	int newCol;

	for (int k = 0; k < 8; ++k)
	{
		int dx = kingDirections[k][0];
		int dy = kingDirections[k][1];

			if (dx == 0 && dy == 0) continue; // 그대로

			newRow = this->pi.row + dx;
			newCol = this->pi.col + dy;

			// 범위 
			if (newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8)
				continue;
			// 위치에 타겟이 있는지 확인하고
			Piece* target = boardctrl->getPiece(newRow,newCol);

			//  오너 값 보고 자기랑 틀려야 이동/공격 되는 방식
			if (target == nullptr || target->getOwner() != this->pi.owner) {
				legalMoves.push_back({ newRow, newCol });
				
				// if (target->getType() == PIECE_ROOK && (target->getRow() == 7 || target->getRow() == 0) && (target->getCol() == 5 || target->getCol() == 4));
			}
	
	}

	return legalMoves;
}

void King::Init() {

	char FileName[256];

	sprintf_s(FileName, "./resource/Img/chess/piece/p_wh_king.png");
	King_whimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/piece/p_bk_king.png");
	King_bkimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}

void King::Draw() {

	int KingX = 400 + pi.col * 110;
	int KingY = 80 + pi.row * 110;

	if (pi.owner == PLAYER) {
		King_whimg.SetColor(255, 255, 255, 255);
		King_whimg.Draw((int)pxy.x + background.posX, (int)pxy.y);
	}

	else if (pi.owner == AI) {
		King_bkimg.SetColor(255, 255, 255, 255);
		King_bkimg.Draw((int)pxy.x + background.posX, (int)pxy.y);
	}
}

void King::Update() {

}