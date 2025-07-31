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

	void SetPiecesStarting();	//기물 기본 위치
	void Init();
	void Draw();

	Piece* getPiece(int row, int col) const;
	void setPiece(int row, int col, Piece* piece);

    struct UndoInfo {
        MoveLogic::Move move;           // 1. 어떤 수를 뒀었는지 from, to 정보
        Piece* capturedPiece;           // 2. 이동 중에 잡았던 기물들을 캡쳐

        int capturedPieceRow;   // 3. 잡혔던 기물이 원래 어느 줄에 있었는지
        int capturedPieceCol;   // 4. 잡혔던 기물이 원래 어느 칸에 있었는지
    };

	UndoInfo ApplyMoveForAI(const MoveLogic::Move &move); // 함수 이름은 AI지만 실제로 보드를 움직이는 함수라 여기다 선언
    void UndoMoveForAI(const UndoInfo &undoInfo);

};




extern BoardController boardctrl;
#endif
