#include "BattleState.h"

// 턴 넘기기
void BattleState::nextTurn() {
    attackerDefending = false;
    defenderDefending = false;
    currentTurn = (currentTurn == TurnOwner::Attacker)
                    ? TurnOwner::Defender
                    : TurnOwner::Attacker;
}
// 누가 죽었나 체크
bool BattleState::checkVictory() 
{
	if (atkHP <= 0) {
		winner = BattleWinner::Defender;
		return true;
	}
	if (defHP <= 0) {
		winner = BattleWinner::Attacker;
		return true;
	}
	return false;
}
