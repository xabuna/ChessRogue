#include "BattleManager.h"

// ���� �ʱ�ȭ. ü���ǿ��� �� ���� �� ȣ��
void BattlePhase::init(Piece* atk, Piece* def) {
	attacker = atk;							// �ú� �� ��
	defender = def;							// �ú� ���� ��
	state.atkHP = atk->getHP();			    // ������ ü�� �ʱ�ȭ
	state.defHP = def->getHP();			    // ������ ü�� �ʱ�ȭ
	state.atkDamage = atk->getDamage();		// ������ ���ݷ�
	state.defDamage = def->getDamage();		// ������ ���ݷ�
	state.atkEvaded = atk->getEvade();		// ������ ȸ����
	state.defEvaded = def->getEvade();		// ������ ȸ����

	state.currentTurn = TurnOwner::Attacker;  // ���� ������ �� ������
	state.isBattleOver = false;
}

// �� �����Ӹ��� ȣ���. ���� ���� ������Ʈ + �� ó�� ��
void BattlePhase::update() {
	if (state.isBattleOver) return;

	// ���⼱ ���¸� ����, ��ư ������ onActionSelected()���� ó��
	if (state.checkVictory()) {
		state.isBattleOver = true;
		// ���⼭ ��� �����ϰų�, GameManager���� ��� �ѱ�
	}
}

// ��ư ������ ȣ���
void BattlePhase::onActionSelected(BattleAction action) {
	if (state.isBattleOver) return;

	if (state.currentTurn == TurnOwner::Attacker) {
		system.ActionButton(attacker, defender, action, state);
	}
	else {
		system.ActionButton(defender, attacker, action, state);
	}

	// �� �ѱ��
	state.nextTurn();
}

// �� �ѱ��
void BattleState::nextTurn() {
	currentTurn = (currentTurn == TurnOwner::Attacker) // 
		? TurnOwner::Defender
		: TurnOwner::Attacker;
}

// ���� �׾��� üũ
bool BattleState::checkVictory() {
	return atkHP <= 0 || defHP <= 0;
}

void BattleSystem::ActionButton(Piece* actor, Piece* target, BattleAction action, BattleState& state) {
	int dmg = actor->getDamage();

	bool targetDefending = (state.currentTurn == TurnOwner::Attacker) ? state.defenderDefending : state.attackerDefending;

	switch (action.type) {
	case BattleActionType::Attack: {
		bool evaded = isEvaded(target);  // ����� ���ߴ��� ����
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
		// ���� �̱���
		break;
	}
}


// ũ��Ƽ�� 
bool BattleSystem::isCriticalHit() {
	int critical = rand() % 100;  // 0~99
	return critical < CRITICAL_HIT_CHANCE;
}

// ȸ��
bool BattleSystem::isEvaded(Piece* hited) {
	int evad = rand() % 100;
	return evad < hited->getEvade();
}