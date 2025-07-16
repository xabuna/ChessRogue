// #include "BattleManager.h"


// // 전투 초기화. 체스판에서 쌈 붙을 때 호출
// void BattlePhase::init(Piece* atk, Piece* def) {
// 	attacker = atk;					// 시비 건 애
// 	defender = def;					// 시비 당한 애
// 	state.atkHP = atk->getHP();     // 공격자 체력 초기화
// 	state.defHP = def->getHP();     // 수비자 체력 초기화
// 	state.currentTurn = TurnOwner::Attacker;  // 누가 먼저냐 → 공격자
// 	state.isBattleOver = false;
// }

// // 매 프레임마다 호출됨. 전투 상태 업데이트 + 턴 처리 등
// void BattlePhase::update() {
// 	if (state.isBattleOver) return;

// 	// 여기선 상태만 보고, 버튼 누르면 onActionSelected()에서 처리
// 	if (state.checkVictory()) {
// 		state.isBattleOver = true;
// 		// 여기서 결과 리턴하거나, GameManager한테 결과 넘김
// 	}
// }

// // 버튼 누르면 호출됨
// void BattlePhase::onActionSelected(BattleAction action) {
// 	if (state.isBattleOver) return;

// 	if (state.currentTurn == TurnOwner::Attacker) {
// 		system.ActionButton(attacker, defender, action, state);
// 	}
// 	else {
// 		system.ActionButton(defender, attacker, action, state);
// 	}

// 	// 턴 넘기기
// 	state.nextTurn();
// }

// // 턴 넘기기
// void BattleState::nextTurn() {
// 	currentTurn = (currentTurn == TurnOwner::Attacker) // 
// 		? TurnOwner::Defender
// 		: TurnOwner::Attacker;
// }

// // 누가 죽었나 체크
// bool BattleState::checkVictory() {
// 	return atkHP <= 0 || defHP <= 0;
// }