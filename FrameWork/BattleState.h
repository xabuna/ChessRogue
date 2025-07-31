#ifndef _BATTLESTATE_H_
#define _BATTLESTATE_H_

#include "Define.h"


class BattleState {
public:
  int atkHP = 0;            // 공격자 체력
  int defHP = 0;            // 수비자 체력
  int atkDamage = 0;		// 공격자 공격력
  int defDamage = 0;		// 수비자 공격력
  int atkEvaded = 0;		// 공격자 회피율
  int defEvaded = 0;		// 수비자 회피율

  TurnOwner currentTurn;    // 지금 누구 차례냐

  bool attackerDefending = false;
  bool defenderDefending = false;

  bool isBattleOver = false;

  BattleWinner winner = BattleWinner::None;

  // 턴 넘기기
  void nextTurn();

  // 누가 죽었나 체크
  bool checkVictory();
};


#endif