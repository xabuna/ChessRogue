#include "Bishop.h"

Bishop::Bishop() {}
Bishop::Bishop(Pieceinfo _pi, PieceXY _pxy, PiecePower _pp, bool alive)
	: Piece(_pi, _pxy, _pp, alive) {}
Bishop::Bishop(Pieceinfo _pi)
	: Piece(_pi) {
	Init();

	setPosition(_pi.row, _pi.col);
}
Bishop::Bishop(PiecePower _pp)
	: Piece(PiecePower{ 60, 1, 20, 10 }) {}
	
Bishop::~Bishop() {}

Bishop::Bishop(const Bishop & _bishop)
	: Piece(_bishop) {
}

Bishop& Bishop::operator=(const Bishop & _bishop) {
	if (this != &_bishop) {
		Piece::operator=(_bishop);
		//추가속성or기능
		//스프라이트 머시기
	}
	return *this;
}

vector<pair<int, int>> Bishop::getLegalMoves(BoardController* boardctrl)
{
	vector<pair<int, int>>legalMoves;
	legalMoves.reserve(16);

	// 대각선 이동
	int bishopDirections[4][2] = {
	{-1, -1},  // ↖
	{-1,  1},  // ↗
	{ 1, -1},  // ↙
	{ 1,  1}   // ↘
	};

	for (int d = 0; d < 4; d++) {
		int dx = bishopDirections[d][0];
		int dy = bishopDirections[d][1];

		int newRow = this->pi.row + dx;
		int newCol = this->pi.col + dy;

		// 한 방향으로만 이동
		while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {

			Piece* target = boardctrl->getPiece(newRow,newCol);

			if (target == nullptr) {
				// 빈 칸이면 이동
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

void Bishop::Init() {

	char FileName[256];

	sprintf_s(FileName, "./resource/Img/chess/piece/p_wh_bishop.png");
	Bishop_whimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/piece/p_bk_bishop.png");
	Bishop_bkimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}

void Bishop::Draw() {
		//시스템 클래스를 만들면 거기 호출되는 함수에 따라 기물이 출력되도록 컬러와 위치만 세팅

		if (pi.owner == PLAYER) {
			Bishop_whimg.SetColor(255, 255, 255, 255);
			Bishop_whimg.Draw((int)pxy.x + background.posX, (int)pxy.y);
		}

		else if (pi.owner == AI) {
			Bishop_bkimg.SetColor(255, 255, 255, 255);
			Bishop_bkimg.Draw((int)pxy.x + background.posX, (int)pxy.y);
		}
}

void Bishop::Update() {

}