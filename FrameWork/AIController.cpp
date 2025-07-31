#include "AIController.h"
#include "PieceCtrl.h"
#include "BoardController.h"
#include "BattleTrigger.h"
#include "Move.h"
#include "Game.h"
#include <Windows.h>

extern PieceCtrl pieceCtrl;
extern BoardController boardctrl;

void AIController::Update() {
    if (pieceCtrl.GetTurn() != AI) return;

    OutputDebugStringA("AIController: AI 턴 처리 시작\n");

    // AI의 딜레이 처리
    if (!pieceCtrl.UpdateAITurnDelay()) return;

    // AI 수 결정
    MoveLogic::Move bestMove = pieceCtrl.GetAIMove(); // 구현된 AI 수 선택 함수
    Piece* attacker = boardctrl.getPiece(bestMove.fromRow, bestMove.fromCol);
    Piece* defender = boardctrl.getPiece(bestMove.toRow, bestMove.toCol);

    // 전투 조건
    if (defender != nullptr && attacker->getTeam() != defender->getTeam()) {
        BattleTrigger::Trigger(attacker, defender);
        return; // 전투로 진입했으므로 턴 넘기지 않음
    }

    // 수 실행
    pieceCtrl.ExecuteMove(bestMove);

    // 턴 넘기기
    pieceCtrl.SwitchTurn();
}