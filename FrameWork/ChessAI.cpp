// ChessAI.cpp 파일
#include "ChessAI.h"
#include "IBoardEvaluator.h"
#include "BoardController.h"
#include <algorithm>
#include <climits>

// 생성자 구현
ChessAI::ChessAI(IBoardEvaluator* evaluator) : currentEvaluator(evaluator) {}

// 모든 가능한 이동을 찾는 함수
std::vector<MoveLogic::Move> ChessAI::GetAllPossibleMoves(BoardController& boardctrl) {
    std::vector<MoveLogic::Move> allPossibleMoves;
    allPossibleMoves.reserve(25); // 미리 공간을 확보

    int aiPieceFoundCount = 0; // 디버깅용: AI 기물이 몇 개 발견되었는지
    int totalLegalMovesCount = 0; // 디버깅용: 발견된 총 합법적 이동 수

    // 보드 조회
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            Piece* currentPiece = boardctrl.getPiece(row, col);

            // 1. 이 칸에 기물이 있는지 확인
            if (currentPiece != nullptr && currentPiece->getAlive()) {
                // 2. 그 기물이 AI 소유인지 확인
                if (currentPiece->getOwner() == AI) {
                    aiPieceFoundCount++; // AI 기물 발견!

                    // 3. 이 기물이 움직일 수 있는 모든 목적지들을 가져옴
                    std::vector<std::pair<int, int>> legalDestinations = currentPiece->getLegalMoves(&boardctrl);

                    if (!legalDestinations.empty()) {
                        totalLegalMovesCount += legalDestinations.size();

                        // 4. 가져온 목적지들마다 Move 객체를 만들어서 추가
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

    // 디버깅 메시지 출력 (Visual Studio 출력 창에 표시됨)
    char debugMsg[256];
    sprintf_s(debugMsg, "AI 기물 수: %d, 합법적 이동 수: %d\n", aiPieceFoundCount, totalLegalMovesCount);
    OutputDebugStringA(debugMsg);

    return allPossibleMoves;
}

// 최적의 이동을 찾는 함수
MoveLogic::Move ChessAI::GetBestMove(BoardController& virtualBoard) {
    int maxScore = INT_MIN; // 가장 낮은 값으로 초기화
    MoveLogic::Move bestMove; // 최고의 수를 저장할 변수

    std::vector<MoveLogic::Move> possibleMoves = GetAllPossibleMoves(virtualBoard);

    // 둘 수 있는 수가 없으면 빈 Move 객체 반환
    if (possibleMoves.empty()) {
        OutputDebugStringA("AI가 둘 수 있는 수가 없음!\n");
        return MoveLogic::Move();
    }

    // 첫 번째 수를 일단 최고라고 가정하고 먼저 평가
    bestMove = possibleMoves[0];
    BoardController::UndoInfo tempUndoInfo = virtualBoard.ApplyMoveForAI(bestMove);
    maxScore = currentEvaluator->Evaluator(virtualBoard); // 첫 번째 수 평가
    virtualBoard.UndoMoveForAI(tempUndoInfo); // 평가 끝났으니 원래대로 돌려놓기
    
    // 나머지 가능한 모든 수 평가
    for (size_t i = 1; i < possibleMoves.size(); ++i) { 
        const MoveLogic::Move& currentMove = possibleMoves[i];

        // 현재 수를 보드에 적용
        BoardController::UndoInfo undoInfo = virtualBoard.ApplyMoveForAI(currentMove);

        // 그리고 보드를 평가
        int currentScore = currentEvaluator->Evaluator(virtualBoard);

        // 점수 비교하면서 최고 점수를 계속 업데이트
        if (currentScore > maxScore) {
            maxScore = currentScore; // 최고 점수 업데이트
            bestMove = currentMove;  // 최고 수 업데이트
        }

        // 보드를 원래대로 되돌림
        virtualBoard.UndoMoveForAI(undoInfo);
    }

    // 디버깅 메시지 출력
    char moveMsg[256];
    sprintf_s(moveMsg, "AI 최적의 수: %d,%d -> %d,%d\n", 
             bestMove.fromRow, bestMove.fromCol, bestMove.toRow, bestMove.toCol);
    OutputDebugStringA(moveMsg);

    return bestMove;
}