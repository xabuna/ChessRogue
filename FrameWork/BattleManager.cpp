#include "BattleManager.h"

// 전투 초기화. 체스판에서 쌈 붙을 때 호출
void BattlePhase::init(Piece* atk, Piece* def) {
	attacker = atk;							// 시비 건 애
	defender = def;							// 시비 당한 애
	state.atkHP = atk->getHP();			    // 공격자 체력 초기화
	state.defHP = def->getHP();			    // 수비자 체력 초기화
	state.atkDamage = atk->getDamage();		// 공격자 공격력
	state.defDamage = def->getDamage();		// 수비자 공격력
	state.atkEvaded = atk->getEvade();		// 공격자 회피율
	state.defEvaded = def->getEvade();		// 수비자 회피율

	state.currentTurn = TurnOwner::Attacker;  // 누가 먼저냐 → 공격자
	state.isBattleOver = false;
}

// 매 프레임마다 호출됨. 전투 상태 업데이트 + 턴 처리 등
void BattlePhase::update() {
	if (state.isBattleOver) return;

	// 여기선 상태만 보고, 버튼 누르면 onActionSelected()에서 처리
	if (state.checkVictory()) {
		state.isBattleOver = true;
		// 여기서 결과 리턴하거나, GameManager한테 결과 넘김
	}
}

// 버튼 누르면 호출됨
void BattlePhase::onActionSelected(BattleAction action) {
	if (state.isBattleOver) return;

	if (state.currentTurn == TurnOwner::Attacker) {
		system.ActionButton(attacker, defender, action, state);
	}
	else {
		system.ActionButton(defender, attacker, action, state);
	}

	// 턴 넘기기
	state.nextTurn();
}

// 턴 넘기기
void BattleState::nextTurn() {
	currentTurn = (currentTurn == TurnOwner::Attacker) // 
		? TurnOwner::Defender
		: TurnOwner::Attacker;
}

// 누가 죽었나 체크
bool BattleState::checkVictory() {
	return atkHP <= 0 || defHP <= 0;
}

void BattleSystem::ActionButton(Piece* actor, Piece* target, BattleAction action, BattleState& state) {
	int dmg = actor->getDamage();

	bool targetDefending = (state.currentTurn == TurnOwner::Attacker) ? state.defenderDefending : state.attackerDefending;

	switch (action.type) {
	case BattleActionType::Attack: {
		bool evaded = isEvaded(target);  // 대상이 피했는지 판정
		if (evaded) {
			//std::cout << "[MISS] Attack was evaded!\n";
			break;
		}

		bool critical = isCriticalHit();
		if (critical) dmg *= CRITICAL_HIT_MULTIPLIER;

		if (targetDefending) dmg /= 2;

		if (state.currentTurn == TurnOwner::Attacker)
			state.defHP -= dmg;
		else
			state.atkHP -= dmg;

		state.attackerDefending = false;
		state.defenderDefending = false;

		//std::cout << (critical ? "[CRITICAL] " : "") << "Damage dealt: " << dmg << std::endl;
		break;
	}

	case BattleActionType::Defend:{
		if (state.currentTurn == TurnOwner::Attacker)
			state.attackerDefending = true;
		else
			state.defenderDefending = true;
		break;
	}
	case BattleActionType::UseItem:
		// 아직 미구현
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