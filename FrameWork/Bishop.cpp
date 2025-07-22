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
		//�߰��Ӽ�or���
		//��������Ʈ �ӽñ�
	}
	return *this;
}

vector<pair<int, int>> Bishop::getLegalMoves(BoardController* boardctrl)
{
	vector<pair<int, int>>legalMoves;
	legalMoves.reserve(16);

	// �밢�� �̵�
	int bishopDirections[4][2] = {
	{-1, -1},  // ��
	{-1,  1},  // ��
	{ 1, -1},  // ��
	{ 1,  1}   // ��
	};

	for (int d = 0; d < 4; d++) {
		int dx = bishopDirections[d][0];
		int dy = bishopDirections[d][1];

		int newRow = this->pi.row + dx;
		int newCol = this->pi.col + dy;

		// �� �������θ� �̵�
		while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {

			Piece* target = boardctrl->getPiece(newRow,newCol);

			if (target == nullptr) {
				// �� ĭ�̸� �̵�
				legalMoves.push_back({ newRow, newCol });
			}
			else { // ���� ������
				if (target->getOwner() != this->pi.owner) {
					// �����϶�!
					legalMoves.push_back({ newRow, newCol });
				}
				break; // ���� ������ �� �̻� �̵����� ����
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
		//�ý��� Ŭ������ ����� �ű� ȣ��Ǵ� �Լ��� ���� �⹰�� ��µǵ��� �÷��� ��ġ�� ����

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