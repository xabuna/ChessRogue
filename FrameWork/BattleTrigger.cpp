#include "Include.h"

void BattleTrigger::Trigger(Piece* attacker, Piece* defender) {

 //   OutputDebugStringA("BattleManager::Trigger È£Ãâ\n");
    if (!attacker || !defender) {
       // OutputDebugStringA("!attacker || !defender return; È£ÃâµÊ\n");
        return;
    }
    if (attacker->getHP() <= 0 || defender->getHP() <= 0) {
       // OutputDebugStringA("attacker->getHP() !defender return; È£ÃâµÊ\n");
        return;
    }

    BattleManager::GetInstance().StartBattle(attacker, defender);

}