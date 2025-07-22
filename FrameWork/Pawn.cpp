#include "Pawn.h"

Pawn::Pawn() {}

Pawn::Pawn(Pieceinfo _pi, PieceXY _pxy, PiecePower _pp, bool alive)
	: Piece(_pi, _pxy, _pp, alive) {
}
Pawn::Pawn(Pieceinfo _pi)
	: Piece(_pi) {
	Init();

	setPosition(_pi.row, _pi.col);
}

Pawn::Pawn(PiecePower _pp) 
	: Piece(_pp) {
	pp.hp =			20;
	pp.ap =			1;
	pp.damage =		10;
	pp.evade =		10;
}

Pawn::~Pawn() {
	//딜리트 스프라이트
}

Pawn::Pawn(const Pawn& _pawn)
	: Piece(_pawn) {
}

Pawn& Pawn::operator=(const Pawn& _pawn) {
	if (this != &_pawn) {
		Piece::operator=(_pawn);
		//추가속성or기능
		//스프라이트 머시기
	}
	return *this;
}

std::vector<pair<int, int>> Pawn::getLegalMoves(BoardController* boardctrl)
{
	int p_move{}; // 플레이어 인지 AI인지 판단
	int oneStep_Row; // 한 칸 이동 할 곳
	int twoStep_Row; // 두 칸 이동 할 곳 ( 처음 한 번만)
	int p_col; // 움직이는 폰의 열의 값을 갖고옴
	int startRow{}; // 처음 행 ( 두칸 움직 일 수 있는지 판단)


    std::vector<pair<int, int>>legalMoves;
	legalMoves.reserve(4); // 폰의 최대 이동 가능한 수 4개라서 4만큼 메모리 확보

	if (pi.owner == PLAYER) {
		p_move = -1; // 플레이어는 밑이라서 -1 해야 위로 올라감
	}
	else if (pi.owner == AI) {
		p_move = 1; // 플레이어와 반대로 위라서 1
	}

	if (pi.owner == PLAYER && pi.row == 6) {
		startRow = 6;
	}
	else if (pi.owner == AI && pi.row == 1) {
		startRow = 1;
	}

	p_col = pi.col;
	twoStep_Row = pi.row + 2 * p_move;
	// 한 칸 앞으로 갈 때
	oneStep_Row = pi.row + p_move;
	if (oneStep_Row >= 0 && oneStep_Row < 8 && boardctrl->getPiece(oneStep_Row,p_col) == nullptr) {
		legalMoves.push_back({ oneStep_Row, p_col });
		// 두 칸 앞으로 갈 때 (처음 움직일 때만)
		if (pi.row == startRow && twoStep_Row >= 0 && twoStep_Row < 8 && boardctrl->getPiece(twoStep_Row, p_col) == nullptr) { // 앞에 기물이 있는지 없는지 판단
			legalMoves.push_back({ twoStep_Row, p_col });
		}
	}

	// 대각선 공격

	for (int dc = -1; dc <= 1; dc += 2) {
		int new_col = pi.col + dc;
		if (new_col < 0 || new_col >= 8) continue;

		// 위치에 타겟이 있는지 확인하고 오너 값 보고 자기랑 틀려야 공격 되는 방식
		Piece* target = boardctrl->getPiece(oneStep_Row,new_col);
		if (target != nullptr && target->getOwner() != this->pi.owner) {
			legalMoves.push_back({ oneStep_Row, new_col });
		}
	}

	return legalMoves;
}

void Pawn::Init() {

	char FileName[256];

	sprintf_s(FileName, "./resource/Img/chess/piece/p_wh_pawn.png");
	Pawn_whimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/piece/p_bk_pawn.png");
	Pawn_bkimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}

void Pawn::Draw() {
	//시스템 클래스를 만들면 거기 호출되는 함수에 따라 기물이 출력되도록 컬러와 위치만 세팅

	/*int PawnX = 400 + pi.col * 110;
	int PawnY = 80 + pi.row * 110;*/

	if (pi.owner == PLAYER) {
		Pawn_whimg.SetColor(255, 255, 255, 255);
		Pawn_whimg.Draw((int)pxy.x + background.posX, (int)pxy.y);
	}

	else if (pi.owner == AI) {
		Pawn_bkimg.SetColor(255, 255, 255, 255);
		Pawn_bkimg.Draw((int)pxy.x + background.posX, (int)pxy.y);
	}
}

void Pawn::Update() {

}