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
	//����Ʈ ��������Ʈ
}

Pawn::Pawn(const Pawn& _pawn)
	: Piece(_pawn) {
}

Pawn& Pawn::operator=(const Pawn& _pawn) {
	if (this != &_pawn) {
		Piece::operator=(_pawn);
		//�߰��Ӽ�or���
		//��������Ʈ �ӽñ�
	}
	return *this;
}

std::vector<pair<int, int>> Pawn::getLegalMoves(BoardController* boardctrl)
{
	int p_move{}; // �÷��̾� ���� AI���� �Ǵ�
	int oneStep_Row; // �� ĭ �̵� �� ��
	int twoStep_Row; // �� ĭ �̵� �� �� ( ó�� �� ����)
	int p_col; // �����̴� ���� ���� ���� �����
	int startRow{}; // ó�� �� ( ��ĭ ���� �� �� �ִ��� �Ǵ�)


    std::vector<pair<int, int>>legalMoves;
	legalMoves.reserve(4); // ���� �ִ� �̵� ������ �� 4���� 4��ŭ �޸� Ȯ��

	if (pi.owner == PLAYER) {
		p_move = -1; // �÷��̾�� ���̶� -1 �ؾ� ���� �ö�
	}
	else if (pi.owner == AI) {
		p_move = 1; // �÷��̾�� �ݴ�� ���� 1
	}

	if (pi.owner == PLAYER && pi.row == 6) {
		startRow = 6;
	}
	else if (pi.owner == AI && pi.row == 1) {
		startRow = 1;
	}

	p_col = pi.col;
	twoStep_Row = pi.row + 2 * p_move;
	// �� ĭ ������ �� ��
	oneStep_Row = pi.row + p_move;
	if (oneStep_Row >= 0 && oneStep_Row < 8 && boardctrl->getPiece(oneStep_Row,p_col) == nullptr) {
		legalMoves.push_back({ oneStep_Row, p_col });
		// �� ĭ ������ �� �� (ó�� ������ ����)
		if (pi.row == startRow && twoStep_Row >= 0 && twoStep_Row < 8 && boardctrl->getPiece(twoStep_Row, p_col) == nullptr) { // �տ� �⹰�� �ִ��� ������ �Ǵ�
			legalMoves.push_back({ twoStep_Row, p_col });
		}
	}

	// �밢�� ����

	for (int dc = -1; dc <= 1; dc += 2) {
		int new_col = pi.col + dc;
		if (new_col < 0 || new_col >= 8) continue;

		// ��ġ�� Ÿ���� �ִ��� Ȯ���ϰ� ���� �� ���� �ڱ�� Ʋ���� ���� �Ǵ� ���
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
	//�ý��� Ŭ������ ����� �ű� ȣ��Ǵ� �Լ��� ���� �⹰�� ��µǵ��� �÷��� ��ġ�� ����

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