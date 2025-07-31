#include "Include.h"

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
void BattlePhase::update(double deltaTime) {
	if (state.isBattleOver) return;

	if (state.checkVictory()) {
		state.isBattleOver = true;
		// 결과 처리 로직 (게임매니저에 알리기 등)
		return;
	}
	// HP바 표시
	battleUI.SetHP(state.atkHP, attacker->getMaxHP(), state.defHP, defender->getMaxHP());
	// 전투 메시지
	battleUI.UpdateMessage(deltaTime);

	// AI 행동 쿨타임이 남아있으면 카운트만
	if (aiActionCooldown > 0.0) {
		aiActionCooldown -= deltaTime;
		return;
	}

	// AI 턴 자동 실행 조건: 현재 턴이 AI이고, AI 행동이 아직 처리되지 않았을 때
	if (IsAITurn() && !aiTurnProcessed) {
		aiTurnProcessed = true;  // 중복 실행 방지

		BattleAction aiAction = DecideAIAction();  // AI 행동 결정 함수 (직접 구현 필요)
		onActionSelected(aiAction);

		aiActionCooldown = 0.3; // 행동 후 딜레이 설정 (0.3초 정도)

		return;  // AI 턴 처리 후 즉시 리턴
	}

	// 플레이어 턴이거나 AI 턴 처리 완료 시 리셋 플래그
	if (!IsAITurn()) {
		aiTurnProcessed = false;
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

bool BattlePhase::IsAITurn() const {
	return state.currentTurn == TurnOwner::Defender;
}

// AI 행동 결정 예제 (단순 랜덤 선택)
BattleAction BattlePhase::DecideAIAction() {
	BattleAction action;

	// AI는 공격 70%, 방어 30% 비율로 결정 (임의 조절 가능)
	int r = rand() % 100;
	if (r < 70) {
		action.type = BattleActionType::Attack;
	}
	else {
		action.type = BattleActionType::Defend;
	}

	return action;
}

bool BattlePhase::isOver() const
 { return state.isBattleOver; }
Piece* BattlePhase::getAttacker() const {
	return attacker;
}

Piece* BattlePhase::getDefender() const {
	return defender;
}

PieceType BattlePhase::getAttackerType() const {
	return attacker->getType();
}

PieceType BattlePhase::getDefenderType() const {
	return defender->getType();
}

const BattleState& BattlePhase::getState() const {
	return state;
}