#ifndef _BATTLETRIGGER_H_
#define _BATTLETRIGGER_H_


#include "BattleManager.h"

class Piece;
// 중간 관리자: 전투 시작 트리거
class BattleTrigger {
public:
    static void Trigger(Piece* attacker, Piece* defender);
};
#endif