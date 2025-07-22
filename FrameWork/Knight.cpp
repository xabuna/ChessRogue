#include "Knight.h"

Knight::Knight() {}

Knight::Knight(Pieceinfo _pi, PieceXY _pxy, PiecePower _pp, bool alive)
	: Piece(_pi, _pxy, _pp, alive) {}

Knight::Knight(Pieceinfo _pi)
	: Piece(_pi) {
	Init();

	setPosition(_pi.row, _pi.col);
}
Knight::Knight(PiecePower _pp)
	: Piece(PiecePower{ 50, 1, 20, 20 }) {
}

Knight::~Knight() {
	//딜리트 스프라이트
}

Knight::Knight(const Knight & _knight)
	: Piece(_knight) {
}

Knight& Knight::operator=(const Knight & _knight) {
	if (this != &_knight) {
		Piece::operator=(_knight);
		//추가속성or기능
		//스프라이트 머시기
	}
	return *this;
}

std::vector<pair<int, int>> Knight::getLegalMoves(BoardController* boardctrl)
{
    std::vector<pair<int, int>>legalMoves;
	legalMoves.reserve(8);

	// 나이트는 L자 형태로 이동
	int knightDirections[8][2] = {
		{-2, -1}, {-2, 1}, // 위
		{-1, -2}, {-1, 2}, // 왼쪽
		{1, -2}, {1, 2},   // 오른쪽
		{2, -1}, {2, 1}    // 아래
	};
	int newRow, newCol;

	for (int k = 0; k < 8; k++) {
		newRow = this->pi.row + knightDirections[k][0];
		newCol = this->pi.col + knightDirections[k][1];

		// 범위
		if (newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8) continue;

		// 위치에 타겟 확인
		Piece* target = boardctrl->getPiece(newRow,newCol);

		// 적인지 확인하고 없으면 이동
		if (target == nullptr || target->getOwner() != this->pi.owner) {
			legalMoves.push_back({ newRow, newCol });
		}
		
	}
	return legalMoves;
}

void Knight::Init() {

	char FileName[256];

	sprintf_s(FileName, "./resource/Img/chess/piece/p_wh_knight.png");
	Knight_whimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/piece/p_bk_knight.png");
	Knight_bkimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}

void Knight::Draw() {
	//시스템 클래스를 만들면 거기 호출되는 함수에 따라 기물이 출력되도록 컬러와 위치만 세팅

	if (pi.owner == PLAYER) {
		Knight_whimg.SetColor(255, 255, 255, 255);
		Knight_whimg.Draw((int)pxy.x + background.posX, (int)pxy.y);
	}

	else if (pi.owner == AI) {
		Knight_bkimg.SetColor(255, 255, 255, 255);
		Knight_bkimg.Draw((int)pxy.x + background.posX, (int)pxy.y);
	}
}

void Knight::Update() {

}
