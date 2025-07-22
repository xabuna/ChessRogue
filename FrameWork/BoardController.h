#ifndef _BOARDCONTROLLER_H_
#define _BOARDCONTROLLER_H_

#include "include.h"
#include <vector>

class Piece;
// class Pawn;
// class Bishop;
// class Knight;
// class Rook;
// class Queen;
// class King;

namespace MoveLogic {
	struct Move;
}

using namespace MoveLogic;

class BoardController {
private:

public:

	Piece* board[BOARD_SIZE][BOARD_SIZE];

	BoardController();
	~BoardController();

	std::vector<Piece*> ownedPieces;

	void SetPiecesStarting();	//�⹰ �⺻ ��ġ
	void Init();
	void Draw();

	Piece* getPiece(int row, int col) const;
	void setPiece(int row, int col, Piece* piece);

    struct UndoInfo {
        MoveLogic::Move move;           // 1. � ���� �׾����� from, to ����
        Piece* capturedPiece;           // 2. �̵� �߿� ��Ҵ� �⹰���� ĸ��

        int capturedPieceRow;   // 3. ������ �⹰�� ���� ��� �ٿ� �־�����
        int capturedPieceCol;   // 4. ������ �⹰�� ���� ��� ĭ�� �־�����
    };

	UndoInfo ApplyMoveForAI(const MoveLogic::Move &move); // �Լ� �̸��� AI���� ������ ���带 �����̴� �Լ��� ����� ����
    void UndoMoveForAI(const UndoInfo &undoInfo);

};




extern BoardController boardctrl;
#endif
