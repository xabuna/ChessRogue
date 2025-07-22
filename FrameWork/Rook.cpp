#include "Rook.h"

Rook::Rook() {}

Rook::Rook(Pieceinfo _pi, PieceXY _pxy, PiecePower _pp, bool alive)
	: Piece(_pi, _pxy, _pp, alive) {}

Rook::Rook(Pieceinfo _pi)
	: Piece(_pi) {
	Init();

	setPosition(_pi.row, _pi.col);
}
Rook::Rook(PiecePower _pp)
	: Piece(PiecePower{ 70, 1, 30, 10 }) {
}

Rook::~Rook() {
	//딜리트 스프라이트
}

Rook::Rook(const Rook& _rook)
	: Piece(_rook) {
}

Rook& Rook::operator=(const Rook& _rook) {
	if (this != &_rook) {
		Piece::operator=(_rook);
		//추가속성or기능
		//스프라이트 머시기
	}
	return *this;
}

vector<pair<int, int>> Rook::getLegalMoves(BoardController* boardctrl)
{
	vector<pair<int, int>>legalMoves;
	legalMoves.reserve(14); // 14칸

	

	// 직선 이동
	int rookDirections[4][2] = {
		{-1, 0},  // 위
		{1, 0},   // 아래
		{0, -1},  // 왼쪽
		{0, 1}    // 오른쪽
	};

	int startRow{}; // 캐슬링
	int startColLeft{}; // 캐슬링
	int startColRight{};

    if (pi.owner == PLAYER && pi.row == 6) {
        startRow = 7;
		startColLeft = 0;
		startColRight = 7;
    }
    else if (pi.owner == AI && pi.row == 1) {
        startRow = 0;
        startColLeft = 0;
        startColRight = 7;
    }

	int newRow, newCol;

	for (int r = 0; r < 4; r++) {
		int dx = rookDirections[r][0];
		int dy = rookDirections[r][1];

		newRow = this->pi.row + dx;
		newCol = this->pi.col + dy;

		// 한 개의 방향으로만 이동

		while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
		{
			Piece* target = boardctrl->getPiece(newRow,newCol);
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

void Rook::Init() {

	char FileName[256];

	sprintf_s(FileName, "./resource/Img/chess/piece/p_wh_rook.png");
	Rook_whimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/piece/p_bk_rook.png");
	Rook_bkimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}

void Rook::Draw() {

	if (pi.owner == PLAYER) {
		Rook_whimg.SetColor(255, 255, 255, 255);
		Rook_whimg.Draw((int)pxy.x + background.posX, (int)pxy.y);
	}

	else if (pi.owner == AI) {
		Rook_bkimg.SetColor(255, 255, 255, 255);
		Rook_bkimg.Draw((int)pxy.x + background.posX, (int)pxy.y);
	}
}

void Rook::Update() {

}