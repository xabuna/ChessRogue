#ifndef _MOVE_H_
#define _MOVE_H_

namespace MoveLogic {
	struct Move {
		int fromRow;
		int fromCol;
		int toRow;
		int toCol;

		Move(int fr, int fc, int tr, int tc) : fromRow(fr), fromCol(fc), toRow(tr), toCol(tc) {}
		Move() : fromRow(-1), fromCol(-1), toRow(-1), toCol(-1) {} // 유효하지 않은 이동
	};
}
#endif


