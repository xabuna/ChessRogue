#include "BattleSystem.h"
#include "Piece.h"
#include "BattleState.h"

void BattleSystem::ActionButton(Piece* actor, Piece* target, BattleAction action, BattleState& state) {
	int dmg = actor->getDamage();
	bool targetDefending = (state.currentTurn == TurnOwner::Attacker) ? state.defenderDefending : state.attackerDefending;

	std::string attackerName = (state.currentTurn == TurnOwner::Attacker) ? "플레이어" : "AI";
	std::string targetName = (state.currentTurn == TurnOwner::Attacker) ? "AI" : "플레이어";

	switch (action.type) {
	case BattleActionType::Attack: {
		bool evaded = isEvaded(target);
		if (evaded) {
			battleUI.SetMessage(targetName + "가 공격을 회피했다!", 1.5f);
			break;
		}

		bool critical = isCriticalHit();
		if (critical) {
			dmg *= CRITICAL_HIT_MULTIPLIER;
			battleUI.SetMessage("크리티컬 히트! " + attackerName + "가 " + targetName + "에게 " + std::to_string(dmg) + " 데미지를 입혔다!", 1.5f);
		}
		else {
			if (targetDefending) dmg /= 2;
			battleUI.SetMessage(attackerName + "가 " + targetName + "에게 " + std::to_string(dmg) + " 데미지를 입혔다!", 1.5f);
		}

		if (state.currentTurn == TurnOwner::Attacker)
			state.defHP -= dmg;
		else
			state.atkHP -= dmg;

		break;
	}

	case BattleActionType::Defend: {
		if (state.currentTurn == TurnOwner::Attacker)
			state.attackerDefending = true;
		else
			state.defenderDefending = true;

		battleUI.SetMessage(attackerName + "가 방어 자세를 취했다!", 1.5f);
		break;
	}

	case BattleActionType::UseItem:
		battleUI.SetMessage(attackerName + "가 아이템을 사용했다!", 1.5f);
		break;
	}
}


// 크리티컬 
bool BattleSystem::isCriticalHit() {
	int critical = rand() % 100;  // 0~99
	return critical < CRITICAL_HIT_CHANCE;
}

// 회피
bool BattleSystem::isEvaded(Piece* hited) {
	int evad = rand() % 100;
	return evad < hited->getEvade();
}

