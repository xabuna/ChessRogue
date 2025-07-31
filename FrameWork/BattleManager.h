#ifndef _BATTLEMANAGER_H_
#define _BATTLEMANAGER_H_

#include "BattleUI.h"
#include "BoardController.h"
#include "BattlePhase.h" 
#include "Transition.h"
#include "TransitionChar.h"

class Piece;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BattlePhase를 보관하고, 외부에서 전투 API를 호출할 수 있게 하는 매니저
class BattleManager {
private:
    BattlePhase* phase;  // 현재 전투
    bool battlePhaseStarted = false;
  
public:
    BattleManager() {}
    ~BattleManager() {}

    // 전투 시작 (새 BattlePhase 생성)
    void StartBattle(Piece* atk, Piece* def);

    // 매 프레임 호출
    void Draw(HDC hdc);
    void Update(double frame);

    // 버튼 입력 처리
    void PlayerAttack();
    void PlayerDefend();
    void UseItem();

    // 상태 체크용
    bool IsInBattlePhase() const;
    bool HasPhase() const;

    BattlePhase* GetPhase() { return phase; }

    static BattleManager& GetInstance() {
        static BattleManager instance;
        return instance;
    }
};

#endif