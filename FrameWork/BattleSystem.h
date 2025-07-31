#ifndef _BATTLESYSTEM_H_
#define _BATTLESYSTEM_H_

// 순환 참조 방지를 위해 최대한 전방 선언
#include "Define.h"       // BattleAction 정의
class Piece;             // 포인터로만 쓰임 → 전방선언 OK
class BattleState;       // 레퍼런스로만 쓰임 → 전방선언 OK

class BattleSystem {

public:
  void ActionButton(Piece* actor, Piece* target, BattleAction action, BattleState& state); // 버튼 
  bool isCriticalHit(); // 크리티컬
  bool isEvaded(Piece* hitied);		// 회피
};

#endif