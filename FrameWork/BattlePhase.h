#ifndef _BATTLEPHASE_H_
#define _BATTLEPHASE_H_

#include "Piece.h"
#include "BattleUI.h"
#include "BattleState.h"
#include "BattleSystem.h"

class BattleManager;

class BattlePhase {
private:

	Piece* attacker;           // 때리는 놈
	Piece* defender;           // 맞는 놈
	BattleState state;         // 현재 체력, 턴, 전투 종료 여부 다 들고 있음
	BattleSystem system;       // 때리고 맞고 데미지 계산해주는 놈
    BattlePhaseState currentState; // 현재 상태
    

    bool aiTurnProcessed = false; // AI턴
    double aiActionCooldown = 0.0; // AI턴 쿨타임

public:
	// 전투 초기화. 체스판에서 쌈 붙을 때 호출
	void init(Piece* atk, Piece* def);

	// 매 프레임마다 호출됨. 전투 상태 업데이트 + 턴 처리 등
	void update(double frame);

	// 버튼 누르면 호출됨
  void onActionSelected(BattleAction action);

  bool IsAITurn() const;

  BattleAction DecideAIAction();

  bool isOver() const;

  Piece* getAttacker() const;
  Piece* getDefender() const;
  PieceType getAttackerType() const;
  PieceType getDefenderType() const;
  const BattleState& getState() const;
};

#endif