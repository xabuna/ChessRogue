#include "Queen.h"

Queen::Queen() {}

Queen::Queen(Pieceinfo _pi, PieceXY _pxy, PiecePower _pp, bool alive)
	: Piece(_pi, _pxy, _pp, alive) {}

Queen::Queen(Pieceinfo _pi)
	: Piece(_pi) {
	Init();

	setPosition(_pi.row, _pi.col);
}
Queen::Queen(PiecePower _pp)
	: Piece(PiecePower{ 130, 1 , 50, 10 }) {}

Queen::~Queen() {
	//딜리트 스프라이트
}

Queen::Queen(const Queen& _queen)
	: Piece(_queen) {
}

Queen& Queen::operator=(const Queen& _queen) {
	if (this != &_queen) {
		Piece::operator=(_queen);
		//추가속성or기능
		//스프라이트 머시기
	}
	return *this;
}

vector<pair<int, int>> Queen::getLegalMoves(BoardController* boardCtrl)
{
	vector<pair<int, int>>legalMoves;
	legalMoves.reserve(28);

	// 퀸은 룩 + 비숍
	// 우선 룩 처럼
	int queenDirections[8][2] = {
		{-1, 0},   // ↑
		{1, 0},    // ↓
		{0, -1},   // ←
		{0, 1},    // →
		{-1, -1},  // ↖
		{-1,  1},  // ↗
		{ 1, -1},  // ↙
		{ 1,  1}   // ↘
	};

	int newRow, newCol;

	for (int q = 0; q < 8; ++q)
	{
		int dx = queenDirections[q][0];
		int dy = queenDirections[q][1];

		newRow = this->pi.row + dx;
		newCol = this->pi.col + dy;

		// 이 새낀 그냥 무적임
		while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
		{
			Piece* target = boardCtrl->getPiece(newRow, newCol);
			if (target == nullptr) {
				// 적이 없으면 빈 칸이면 이동
				legalMoves.push_back({ newRow, newCol });
			}
			else { // 적이 있으면
				if (target->getOwner() != this->pi.owner) {
					// 공격하라!
					legalMoves.push_back({ newRow, newCol });
				}
				break; // 적이 있으면 더 이상 이동하지 않음
			}
			newRow += dx;
			newCol += dy;
		}

	}

	return legalMoves;
}

void Queen::Init() {

	char FileName[256];

	sprintf_s(FileName, "./resource/Img/chess/piece/p_wh_queen.png");
	Queen_whimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/piece/p_bk_queen.png");
	Queen_bkimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}

void Queen::Draw() {

	if (pi.owner == PLAYER) {
		Queen_whimg.SetColor(255, 255, 255, 255);
		Queen_whimg.Draw((int)pxy.x + background.posX, (int)pxy.y);
	}

	else if (pi.owner == AI) {
		Queen_bkimg.SetColor(255, 255, 255, 255);
		Queen_bkimg.Draw((int)pxy.x + background.posX, (int)pxy.y);
	}
}

void Queen::Update() {

}