#include "Include.h"

Game::Game(): gamephase(GamePhase::BOARD) {}

Game:: ~ Game() {}

Game * Game::instance = nullptr;

Game * Game::getInstance() {
    if (instance == nullptr) {
        instance = new Game();
    }
    return instance;
}

void Game::Init(HWND m_hWnd) {
    this -> m_hWnd = m_hWnd;
    this -> m_hdc = GetDC(m_hWnd);

    background.Init();
    board.Init();

    boardctrl.Init();
    pieceCtrl.HighlightInit();

    transition.Init();
    transitionChar.Init();

    boardUI.InvenInit();
    boardUI.BattlelogInit();

    battleUI.Init();

    Camera::GetInstance() -> SetXCam(0);
    //coll.Init(); sound.Init();
    Gmanager.Init();
    // 데이타 베이스///////////////////
    sql.Init();

    attack_box = btn_battle[0];
    useitem_box = btn_battle[1];
    defence_box = btn_battle[2];
}

void Game::Draw(HDC hdc) {

    background.Draw();
    board.Draw();

    boardctrl.Draw();
    pieceCtrl.HighlightUpdate();

    boardUI.InvenDraw();
    boardUI.BattlelogDraw();


    if (gamephase == GamePhase::MOVE_CAMERA || gamephase == GamePhase::BATTLE)
    {
       // //OutputDebugStringA("Game.Draw: BattleManager.Draw 호출됨\n");
        BattleManager::GetInstance().Draw(hdc);
    }

    //coll.Draw();
    Gmanager.Draw();
    // 데이타 베이스///////////////////

    sql.Draw();
}

// Chap, 재정의 함수 호출
void Game::Update(double frame) {

    char buf[128];
    sprintf_s(buf, "[Game] Phase=%d, posX=%.2f, target=%.2f, transition.active=%d, charFadeIn=%d\n",
        gamephase, background.posX, background.targetStageX, transition.active, transitionChar.charFadeIn);
   // OutputDebugStringA(buf);

    char buf2[128];
    sprintf_s(buf2, "[Game::Update] this=%p, gamephase=%d\n", this, gamephase);
   // OutputDebugStringA(buf2);

    if (!BattleManager::GetInstance().HasPhase()
        && gamephase == GamePhase::MOVE_CAMERA
        && !transition.active) {
        if (background.posX == background.targetStageX) {
            gamephase = GamePhase::BOARD;
        }
    }

    if (gamephase != prevPhase) {
        switch (gamephase) {
            case GamePhase::BOARD:
                fmodsound.BGPlay(fmodsound.FmodBoardBGM);
                break;
            case GamePhase::BATTLE:
                // 여기는 전투 상대에 따라 다르게 재생해야 할 수도 있음
                fmodsound.BGPlay(fmodsound.FmodBattle[BattleManager::GetInstance().GetPhase()->getAttackerType()] - 1);
                break;
            case GamePhase::GAME_OVER:
                // 필요 시 오버용 BGM 재생
                break;
            default:
                fmodsound.BGPlay(fmodsound.FmodMainBGM);
                break;
        }

        prevPhase = gamephase;
    }
    //static int a = 0; if(a == 0) { 	GameTime = GetTickCount(); 	a = 1; }
    static DWORD a = 0;

    if (gamephase == GamePhase::BOARD)
    {
        background.Update(frame);



        if (pieceCtrl.GetTurn() == AI) {
            pieceCtrl.UpdateAITurnDelay();
        }
        //OutputDebugStringA("AI가 턴을 둔다\n");

    }

    if (gamephase == GamePhase::MOVE_CAMERA || gamephase == GamePhase::BATTLE) {
        char buf[64];
        sprintf_s(buf, "Game.Update: phase=%d (0=BOARD,1=MOVE_CAMERA,2=BATTLE)\n", (int)gamephase);
        //OutputDebugStringA(buf);

        background.Update(frame);
        //OutputDebugStringA("Game.cpp에서 backgroud.Update(frame); 호출됨\n");

        transition.Update(frame);
        //OutputDebugStringA("Game.cpp에서 transition.Update(frame); 호출됨\n");

        transitionChar.Update(frame);
        //OutputDebugStringA("Game.cpp에서 transitionChar.Update(frame); 호출됨\n");

        BattleManager::GetInstance().Update(frame);
        //OutputDebugStringA("Game.cpp에서 BattleManager::GetInstance().Update(frame); 호출됨\n");
    }

    //case GamePhase::GAME_OVER:
    //    {
    //        // 조건은 킹이 잡혔을 때 over.Update() 호출 over.Update()에서 화면 alpha=255 후 Onmessage를 통해
    //        // 엔터누르면 menu화면으로 backspace누르면 게임오버 보여주도록 하기
    //        break;
    //    }
 

    if (GetTickCount64() - a > frame) {
        // 공부용
        Camera::GetInstance() -> Update();
        key.Update();
        //player.Update();
        coll.Update();


        // 입 맛에 맞게 map.Update(130);
        Gmanager.Update();
        // 데이타 베이스/////////////////// 입 맛에 맞게 (여기선 안쓰임..프레임 값이 필요 할때만.. 그냥 방법만...)
        sql.Update(frame + 3000);

        a = GetTickCount64();
    }

    POINT CursorPos;

    if (GetCursorPos(& CursorPos)) {
        if (m_hWnd) {
            ScreenToClient(m_hWnd, & CursorPos);
        }

        int currentCursorX = CursorPos.x;
        int currentCursorY = CursorPos.y;

        pieceCtrl.HighlightFollow(currentCursorX, currentCursorY);
    } else 
        pieceCtrl.HighlightFollow(-1, -1);

}

void Game::OnMessage(MSG * msg) {

    if (msg -> message == WM_LBUTTONDOWN) {
        POINT mouse;
        mouse.x = LOWORD(msg -> lParam);
        mouse.y = HIWORD(msg -> lParam);

        if (gamephase == GamePhase::BATTLE) {
            battleUI.HandleClick(mouse.x, mouse.y);

            if (PtInRect(& attack_box, mouse)) {
      
                BattleManager::GetInstance().PlayerAttack();
            } else if (PtInRect(& useitem_box, mouse)) {
               
                BattleManager::GetInstance().UseItem();
            } else if (PtInRect(& defence_box, mouse)) {
         
                BattleManager::GetInstance().PlayerDefend();
            }

            return;
        } else if (gamephase == GamePhase::BOARD) {
            POINT boardPos = pieceCtrl.HandleMouseClick(mouse.y, mouse.x);

            if (boardPos.x != -1 && boardPos.y != -1) {
                pieceCtrl.PieceMove(boardPos.y, boardPos.x);
            }
        }
    }

    if (msg -> message == WM_KEYDOWN) {
        if (msg -> wParam == VK_RETURN) {

            switch (gamephase) {
                case GamePhase::BOARD:

                    background.targetStageX = -1680;
                    background.StartTransition();
                    transitionChar.Start();
                    gamephase = GamePhase::MOVE_CAMERA;

                    break;

                case GamePhase::MOVE_CAMERA:

                    break;

                case GamePhase::BATTLE:
                    background.targetStageX = 0;
                    battleUI.battleEnd();
                    battleStarted = OFF;
                    gamephase = GamePhase::MOVE_CAMERA;
                    break;
            }
        }
    }
}

HDC Game::GetHDC() {
    return m_hdc;
}

void Game::SetHDC(HDC hdc) {
    m_hdc = hdc;
}
