// ChessAI.cpp ����
#include "ChessAI.h"
#include "IBoardEvaluator.h"
#include "BoardController.h"
#include <algorithm>
#include <climits>

// ������ ����
ChessAI::ChessAI(IBoardEvaluator* evaluator) : currentEvaluator(evaluator) {}

// ��� ������ �̵��� ã�� �Լ�
std::vector<MoveLogic::Move> ChessAI::GetAllPossibleMoves(BoardController& boardctrl) {
    std::vector<MoveLogic::Move> allPossibleMoves;
    allPossibleMoves.reserve(25); // �̸� ������ Ȯ��

    int aiPieceFoundCount = 0; // ������: AI �⹰�� �� �� �߰ߵǾ�����
    int totalLegalMovesCount = 0; // ������: �߰ߵ� �� �չ��� �̵� ��

    // ���� ��ȸ
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            Piece* currentPiece = boardctrl.getPiece(row, col);

            // 1. �� ĭ�� �⹰�� �ִ��� Ȯ��
            if (currentPiece != nullptr && currentPiece->getAlive()) {
                // 2. �� �⹰�� AI �������� Ȯ��
                if (currentPiece->getOwner() == AI) {
                    aiPieceFoundCount++; // AI �⹰ �߰�!

                    // 3. �� �⹰�� ������ �� �ִ� ��� ���������� ������
                    std::vector<std::pair<int, int>> legalDestinations = currentPiece->getLegalMoves(&boardctrl);

                    if (!legalDestinations.empty()) {
                        totalLegalMovesCount += legalDestinations.size();

                        // 4. ������ �������鸶�� Move ��ü�� ���� �߰�
                        for (const auto& dest : legalDestinations) {
                            int toRow = dest.first;
                            int toCol = dest.second;
                            allPossibleMoves.push_back(MoveLogic::Move(row, col, toRow, toCol));
                        }
                    }
                }
            }
        }
    }

    // ����� �޽��� ��� (Visual Studio ��� â�� ǥ�õ�)
    char debugMsg[256];
    sprintf_s(debugMsg, "AI �⹰ ��: %d, �չ��� �̵� ��: %d\n", aiPieceFoundCount, totalLegalMovesCount);
    OutputDebugStringA(debugMsg);

    return allPossibleMoves;
}

// ������ �̵��� ã�� �Լ�
MoveLogic::Move ChessAI::GetBestMove(BoardController& virtualBoard) {
    int maxScore = INT_MIN; // ���� ���� ������ �ʱ�ȭ
    MoveLogic::Move bestMove; // �ְ��� ���� ������ ����

    std::vector<MoveLogic::Move> possibleMoves = GetAllPossibleMoves(virtualBoard);

    // �� �� �ִ� ���� ������ �� Move ��ü ��ȯ
    if (possibleMoves.empty()) {
        OutputDebugStringA("AI�� �� �� �ִ� ���� ����!\n");
        return MoveLogic::Move();
    }

    // ù ��° ���� �ϴ� �ְ��� �����ϰ� ���� ��
    bestMove = possibleMoves[0];
    BoardController::UndoInfo tempUndoInfo = virtualBoard.ApplyMoveForAI(bestMove);
    maxScore = currentEvaluator->Evaluator(virtualBoard); // ù ��° �� ��
    virtualBoard.UndoMoveForAI(tempUndoInfo); // �� �������� ������� ��������
    
    // ������ ������ ��� �� ��
    for (size_t i = 1; i < possibleMoves.size(); ++i) { 
        const MoveLogic::Move& currentMove = possibleMoves[i];

        // ���� ���� ���忡 ����
        BoardController::UndoInfo undoInfo = virtualBoard.ApplyMoveForAI(currentMove);

        // �׸��� ���带 ��
        int currentScore = currentEvaluator->Evaluator(virtualBoard);

        // ���� ���ϸ鼭 �ְ� ������ ��� ������Ʈ
        if (currentScore > maxScore) {
            maxScore = currentScore; // �ְ� ���� ������Ʈ
            bestMove = currentMove;  // �ְ� �� ������Ʈ
        }

        // ���带 ������� �ǵ���
        virtualBoard.UndoMoveForAI(undoInfo);
    }

    // ����� �޽��� ���
    char moveMsg[256];
    sprintf_s(moveMsg, "AI ������ ��: %d,%d -> %d,%d\n", 
             bestMove.fromRow, bestMove.fromCol, bestMove.toRow, bestMove.toCol);
    OutputDebugStringA(moveMsg);

    return bestMove;
}