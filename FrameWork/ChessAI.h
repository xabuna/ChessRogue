#ifndef _CHESSAIH
#define _CHESSAIH

#include <algorithm>
#include <climits>
#include <vector>
#include "Move.h" // Move ����ü�� ���ǵ� ��� ���� ���� ����
#include "Include.h" // �ٸ� �ʿ��� �����

class IBoardEvaluator;
class BoardController;

// using namespace MoveLogic; // ��������� ���ӽ����̽� using�� �����߾�

class ChessAI {
public:
    //ChessAI();
    ChessAI(IBoardEvaluator* evaluator);// �� �Լ��� ���ڷ� �޴� ������

    IBoardEvaluator* currentEvaluator;

    // AI�� �⹰�� ������ �� �ִ� ��� ����� ��
    std::vector<MoveLogic::Move> GetAllPossibleMoves(BoardController& boardctrl);

    // (!!) Ź���� �� �Դϴ�.
    MoveLogic::Move GetBestMove(BoardController& virtualBoard);
};

#endif