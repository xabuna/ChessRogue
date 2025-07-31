#include "Include.h"

void BattleManager::PlayerAttack() {
    if (!phase || phase->isOver()) return;

    BattleAction action;
    action.type = BattleActionType::Attack;
    phase->onActionSelected(action);
}

void BattleManager::PlayerDefend() {
    if (!phase || phase->isOver()) return;

    BattleAction action;
    action.type = BattleActionType::Defend;
    phase->onActionSelected(action);
}

void BattleManager::UseItem() {
    if (!phase || phase->isOver()) return;

    BattleAction action;
    action.type = BattleActionType::UseItem;
    phase->onActionSelected(action);
}

bool BattleManager::IsInBattlePhase() const
{
	return phase != nullptr && !phase->isOver();
}

bool BattleManager::HasPhase() const {
	return phase != nullptr;
}

void BattleManager::StartBattle(Piece* atk, Piece* def) {
	//OutputDebugStringA("StartBattle 호출됨\n");

	if (phase) delete phase;

	phase = new BattlePhase();
	phase->init(atk, def);

	char buf[64];
	sprintf_s(buf, "StartBattle: phase 초기화됨? %p\n", phase);
	//OutputDebugStringA(buf);

	char atk2[64];
	sprintf_s(atk2, "Atk HP: %d 호출됨\n", atk->getHP());
	//OutputDebugStringA(atk2);

	char def2[64];
	sprintf_s(def2, "Def HP: %d 호출됨\n", def->getHP());
	//OutputDebugStringA(def2);

	if (fabs(background.posX - (-1680)) < 1.0f) 
	{
		//OutputDebugStringA("BattleManager::StartBattle 여기서 if 호출됨\n");
		background.posX = 0;
	}

	background.targetStageX = -1680;
	background.StartTransition();
	
	transitionChar.Start();
	transition.Start();

	Game::getInstance()->gamephase = GamePhase::MOVE_CAMERA;
}

void BattleManager::Update(double frame) {
	//OutputDebugStringA("BattleManager.Update: 호출됨\n");

	float dist = fabs(background.posX - background.targetStageX);

	if (dist > 1.0f) {
		//OutputDebugStringA("BattleManager.Update: 아직 카메라 이동 중\n");
		return;
	}

	if (transition.active || transitionChar.charFadeIn) {
		//OutputDebugStringA("BattleManager.Update: 트랜지션 진행 중, 대기\n");
		return;
	}

	if (!battlePhaseStarted) {
		//OutputDebugStringA("BattleManager.Update: 이동 완료 + 트랜지션 끝남\n");
		transitionChar.Stop();
		transition.Stop();

		battleUI.battleStart();
		Game::getInstance()->gamephase = GamePhase::BATTLE;
		battlePhaseStarted = true;  // 상태 전환 완료 표시
		//OutputDebugStringA("BattleManager.Update: 페이즈를 BATTLE로 전환\n");
		return;  // 다음 프레임부터 battle phase 진행
	}

	if (Game::getInstance()->gamephase == GamePhase::BATTLE) {
		if (!phase) return;

		phase->update(frame);
		//OutputDebugStringA("if (Game::getInstance) phase->update(frame);\n");

		battleUI.SetHP
			(phase->getState().atkHP, phase->getAttacker()->getMaxHP(),	
			 phase->getState().defHP, phase->getDefender()->getMaxHP());

		battleUI.UpdateMessage(frame);
		battleUI.UpdatePiece(frame);
		battleUI.UpdateBtn(frame);

		if (phase->isOver()) 
		{
			// 전투 종료 시 처리
			Piece* atk = phase->getAttacker();
			Piece* def = phase->getDefender();
			BattleWinner win = phase->getState().winner;

			const BattleState& st = phase->getState();

			// 전투 상태를 실기물에 적용
			atk->setHP(st.atkHP);
			def->setHP(st.defHP);
		
		// 공격 기물이 승리 후 공격 기물 위치를 수비 기물 위치로 이동
			if (win == BattleWinner::Attacker)
			{
				// 1. 이동 전 원래 좌표 백업
				int atkPrevRow = atk->getRow();
				int atkPrevCol = atk->getCol();

				int defRow = def->getRow();
				int defCol = def->getCol();

				// 2. 보드에 공격자 위치 업데이트 (수비자 자리에 배치)
				boardctrl.setPiece(defRow, defCol, atk);

				// 3. 공격자 원래 자리 비우기
				boardctrl.setPiece(atkPrevRow, atkPrevCol, nullptr);

				// 5. 실제 객체 좌표도 이동
				atk->setPosition(defRow, defCol);

				// 4. 수비자 제거
				auto it = std::find(boardctrl.ownedPieces.begin(), 
									boardctrl.ownedPieces.end(), def);
				if (it != boardctrl.ownedPieces.end())				
				{
					boardctrl.ownedPieces.erase(it);
				}
				delete def;


				// 5. 실제 객체 좌표도 이동
				atk->setPosition(defRow, defCol);
			}

			else if (win == BattleWinner::Defender) 
			{
				// 수비 기물이 승리 → 공격 기물 제거
				boardctrl.setPiece(atk->getRow(), atk->getCol(), nullptr);

				auto it = std::find(boardctrl.ownedPieces.begin(),
									boardctrl.ownedPieces.end(), atk);
				if (it != boardctrl.ownedPieces.end()) 
				{
					boardctrl.ownedPieces.erase(it);
				}
				delete atk;
			}

			// 전투 Phase 삭제
			delete phase;
			phase = nullptr;

			battleUI.battleEnd();

			battlePhaseStarted = false;
			
			Game::getInstance()->gamephase = GamePhase::BOARD;
			//OutputDebugStringA("BattleManager::Update : gamephase = BOARD\n");
			background.targetStageX = 0;
		}
		
	}
}
	

void BattleManager::Draw(HDC hdc) {
	//OutputDebugStringA("BattleManager.Draw: 함수 진입\n");
	battleUI.Draw(hdc, phase->getAttackerType(), phase->getDefenderType());

	if (!phase) {
		//OutputDebugStringA("BattleManager.Draw: phase == nullptr\n");
		return;
	}
	if(Game::getInstance()->gamephase == GamePhase::MOVE_CAMERA) {
		// 카메라 이동 중 연출
		//OutputDebugStringA("BattleManager.Draw: MOVE_CAMERA 페이즈\n");
		if (transition.active || transitionChar.charFadeIn || transition.m_framecnt > 0.0f) 
		{
			//OutputDebugStringA("BattleManager.Draw: Transition 그리기 조건 통과\n");
			transition.Draw(phase->getDefenderType());
			transitionChar.Draw(phase->getAttackerType(), phase->getDefenderType());
		}
		else { return; }
			//OutputDebugStringA("BattleManager.Draw: Transition 조건 불통과\n");
	}
	else if (Game::getInstance()->gamephase == GamePhase::BATTLE) {
		// 전투 중 연출 (BattleUI 안에서 전투 캐릭터가 올라오므로 그대로 호출)

		//OutputDebugStringA("BattleManager.Draw: 전투 중 연출 (BattleUI 안에서 전투 캐릭터가 올라오므로 그대로 호출\n");
		transition.Draw(phase->getDefenderType());
		transitionChar.Draw(phase->getAttackerType(), phase->getDefenderType());
	}
}
