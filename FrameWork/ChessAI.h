#ifndef _CHESSAIH
#define _CHESSAIH

#include <algorithm>
#include <climits>
#include <vector>
#include "Move.h" // Move 구조체가 정의된 헤더 파일 직접 포함
#include "Include.h" // 다른 필요한 헤더들

class IBoardEvaluator;
class BoardController;

// using namespace MoveLogic; // 헤더에서는 네임스페이스 using을 제거했어

class ChessAI {
public:
    //ChessAI();
    ChessAI(IBoardEvaluator* evaluator);// 평가 함수를 인자로 받는 생성자

    IBoardEvaluator* currentEvaluator;

    // AI가 기물을 움직일 수 있는 모든 경우의 수
    std::vector<MoveLogic::Move> GetAllPossibleMoves(BoardController& boardctrl);

    // (!!) 탁월한 수 입니다.
    MoveLogic::Move GetBestMove(BoardController& virtualBoard);
};

#endif