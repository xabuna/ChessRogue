#include "Include.h"

PieceCtrl pieceCtrl;

void PieceCtrl::HighlightInit() {

    char FileName[256];

    sprintf_s(FileName, "./resource/Img/chess/UIElm/highlight.png");
    Highlight.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}

void PieceCtrl::HighlightDraw(int _row, int _col) {

    if (_col < 0 || _col > 7 || _row < 0 || _row > 7) {
        return;
    }

    int highlightX = BOARDSTART_X + _col * TILE;
    int highlightY = BOARDSTART_Y + _row * TILE;

    Highlight.SetColor(255, 255, 255, 255);
    Highlight.Draw(highlightX + background.posX, highlightY);

}

void PieceCtrl::HighlightUpdate() {
    if (pieceSelected) {
        HighlightDraw(selectedRow, selectedCol);
    }
    //selectedPiece와 겹치지 않는 경우에만
    if (currentRow != -1 && currentCol != -1) {
        // 선택된 칸과 커서 칸이 다를 때만 커서 하이라이트
        if (!(pieceSelected && currentRow == selectedRow && currentCol == selectedCol)) {
            HighlightDraw(currentRow + background.posX, currentCol);
        }
    }
}

void PieceCtrl::HighlightFollow(int currentX, int currentY) {
    POINT InBoard = HandleMouseClick(currentY, currentX);

    if (InBoard.x >= 0 && InBoard.x < 8 && InBoard.y >= 0 && InBoard.y < 8) {
        currentCol = InBoard.x + background.posX;
        currentRow = InBoard.y;
    } else {
        currentCol = -1;
        currentRow = -1;
    }
}

void PieceCtrl::HighlightClear() {
    pieceSelected = false;
    selectedCol = -1;
    selectedRow = -1;
    selectedPiece = nullptr;
}


void PieceCtrl::UpdateAITurnDelay() {
    if (Turn != AI) {
        aiWaiting = false;
        return;
    }

    if (!aiWaiting) {
        // AI 턴 시작된 시점 기록
        aiWaiting = true;
        aiTurnStartTime = GetTickCount64();
        return;
    }

    DWORD now = GetTickCount64();
    if (now - aiTurnStartTime >= 700) {
        ProcessAITurn(); // 0.7초 후 실행
        aiWaiting = false;
    }
}

void PieceCtrl::ClearSelection() {
    pieceSelected = false;
    selectedPiece = nullptr;
    selectedRow = -1;
    selectedCol = -1;
    //ClearHighlight();
}

// 기물 이동 함수 (전투 포함) 반환값은 MoveResult 열거형: Invalid / Moved / BattleStarted
MoveResult PieceCtrl::Move(int fromRow, int fromCol, int toRow, int toCol) {

    // 1. 출발지 기물 확인
    Piece * piece = boardctrl.getPiece(fromRow, fromCol);
    if (!piece) 
        return MoveResult::Invalid; // 출발지에 기물이 없으면 무효 이동
    
    // 2. 이동 가능 위치인지 확인
    vector<pair<int, int>> legalMoves = piece -> getLegalMoves(& boardctrl);
    if (find(legalMoves.begin(), legalMoves.end(), make_pair(toRow, toCol)) == legalMoves.end()) 
        return MoveResult::Invalid; // 이동 불가한 위치면 무효
    
    // 3. 목적지 기물 조사
    Piece * target = boardctrl.getPiece(toRow, toCol);

    // 3-1. 적 기물이 있을 경우 전투 진입
    if (target && target -> getOwner() != piece -> getOwner()) {

        BattleTrigger::Trigger(piece, target);

        SwitchTurn();
        return MoveResult::BattleStarted; // 전투 진입 결과 반환
    }

    // 3-2. 목적지에 아군 기물이 있을 경우 → 이동 불가
    if (target && target -> getOwner() == piece -> getOwner()) 
        return MoveResult::Invalid;
    
    // 4. 일반 이동 처리 (빈 칸)
    if (target) {
        boardctrl.setPiece(toRow, toCol, nullptr); // 기존 적 제거
        delete target; // 메모리 해제
    }

    // 보드 갱신: 새 위치에 기물 설정
    boardctrl.setPiece(toRow, toCol, piece);
    boardctrl.setPiece(fromRow, fromCol, nullptr);

    // 기물 내부 좌표 갱신
    piece -> setPosition(toRow, toCol);

    return MoveResult::Moved; // 정상 이동 완료


}



// PieceCtrl::Move (const Move& move) <<< 오버로드된 함수 (AI가 주로 호출할 함수)
MoveResult PieceCtrl::Move(const MoveLogic::Move & move) {
    // Move 구조체에서 from/to 정보를 추출하여 기존 Move 함수를 호출 이렇게 하면 기존 Move 함수의 복잡한 로직을 쉽게 재사용할
    // 수 있음
    return Move(move.fromRow, move.fromCol, move.toRow, move.toCol);
}

void PieceCtrl::UpdatePos(Piece * piece, int toRow, int toCol) {
    piece -> setPosition(toRow, toCol);
}

void PieceCtrl::Remove(int col, int row) {

    boardctrl.setPiece(row, col, nullptr);

    // 만약 제거된 기물의 메모리를 해제해야 한다면 (예: 기물이 동적 할당되었고, 더 이상 사용되지 않을 때) Piece*
    // removedPiece = boardctrl.getPiece(row, col);  제거되기 전 기물 가져오기 if
    // (removedPiece) {     delete removedPiece;  메모리 해제     boardctrl.setPiece(row,
    // col, nullptr);
}

bool PieceCtrl::Promotable(Piece * piece) {
    return true;
}

void PieceCtrl::PieceMove(int fromRow, int fromCol) {
    POINT pClick = HandleMouseClick(fromRow, fromCol);

    if (pClick.x < 0 || pClick.x >= 8 || pClick.y < 0 || pClick.y >= 8) 
        return; // 범위 밖 클릭이면 아무것도 안 함
    
    if (!pieceSelected) { // 기물이 선택되지 않았을 때 참

        selectedPiece = boardctrl.getPiece(pClick.y, pClick.x); // 참조
        // 1단계: 기물 선택
        if (selectedPiece && selectedPiece -> getOwner() == Turn) { // == Turn으로 owner와 같은 턴일 때만 움직일 수 있게
            selectedCol = pClick.x;
            selectedRow = pClick.y;
            pieceSelected = true;
        }
    } else { // 2번째 클릭을 할 때 이미 기물이 선택 되어있으니까 pieceSelected = true; 라서 else로 이동

        // 2단계: 기물 이동 시도

        MoveResult result = Move(selectedRow, selectedCol, pClick.y, pClick.x);

        // 성공이든 실패든 선택 초기화
        pieceSelected = false;
        selectedCol = -1;
        selectedRow = -1;
        selectedPiece = nullptr;

        switch (result) {
            case MoveResult::Moved:
                SwitchTurn(); // 일반 이동 성공 → 턴 넘김

                break;

            case MoveResult::BattleStarted:
                // 전투 모드 진입 중이므로, 턴 넘기지 않고 대기
                break;

            case MoveResult::Invalid:
            default:
                // 이동 실패, 아무것도 하지 않음
                break;
        }

        // 하이라이트 지우기 clearHighlight();
    }
}

void PieceCtrl::SwitchTurn() {
    // 정말 단순하게 턴만 바꾸기
    Turn = (Turn == PLAYER)
        ? AI
        : PLAYER;
}

void PieceCtrl::ProcessAITurn() {
    // 현재 턴이 AI가 아니라면 아무것도 하지 않음
    if (Turn != AI) {
        return;
    }

    OutputDebugStringA("ProcessAITurn 함수 호출됨: AI 턴\n");

    IBoardEvaluator * evaluator = nullptr; // evaluator를 try/catch 밖에서 선언 및 초기화

    try {
        // 1단계: AI 객체 생성 (평가기 포함)
        evaluator = new BasicMaterialEvaluator();
        ChessAI ai(evaluator);

        // 2단계: AI에게 최적의 수 요청
        MoveLogic::Move bestMove = ai.GetBestMove(boardctrl);

        // 2-1. 유효한 수가 아니면 턴 넘기고 종료
        if (bestMove.fromRow == -1 || bestMove.fromCol == -1 || bestMove.toRow == -1 || bestMove.toCol == -1) {
            OutputDebugStringA("AI: 유효한 수를 찾지 못함 (GetBestMove 반환값 무효)\n");
            Turn = PLAYER;
            return;
        }

        // 3단계: AI 수 실행
        MoveResult result = Move(bestMove);

        char moveDebugMsg[256]; // 디버깅 메시지 출력
        sprintf_s(
            moveDebugMsg,
            "AI가 %d,%d -> %d,%d 이동 시도. 결과: %d\n",
            bestMove.fromRow,
            bestMove.fromCol,
            bestMove.toRow,
            bestMove.toCol,
            static_cast<int>(result)
        );
        //OutputDebugStringA(moveDebugMsg);

        // 4단계: 결과에 따른 처리
        switch (result) {
            case MoveResult::Moved:
                OutputDebugStringA("AI 일반 이동 성공. 턴을 플레이어에게 넘깁니다.\n");
                Turn = PLAYER;
                break;

            case MoveResult::BattleStarted:
                OutputDebugStringA("AI가 전투를 시작함. 턴 유지 (전투 후 처리 예상).\n");
                // 전투가 끝나면 BattleManager나 외부 로직에서 턴을 넘기도록 처리할 것
                break;

            case MoveResult::Invalid:
            default:
                OutputDebugStringA("AI 이동 실패 또는 무효. 턴을 플레이어에게 넘깁니다.\n");
                Turn = PLAYER;
                break;
        }
    } catch (const std::bad_alloc & e) {
        char errorMsg[256];
        sprintf_s(errorMsg, "ProcessAITurn: 메모리 할당 실패 - %s\n", e.what());
        OutputDebugStringA(errorMsg);
        Turn = PLAYER;
    } catch (const std::exception & e) {
        char errorMsg[256];
        sprintf_s(errorMsg, "ProcessAITurn: 예외 발생 - %s\n", e.what());
        OutputDebugStringA(errorMsg);
        Turn = PLAYER;
    } catch (...) {
        OutputDebugStringA("ProcessAITurn: 알 수 없는 예외 발생!\n");
        Turn = PLAYER;
    }

    // 5단계: 평가기 해제
    if (evaluator) {
        delete evaluator;
        evaluator = nullptr;
    }
}
POINT PieceCtrl::HandleMouseClick(int mouseY, int mouseX) {
    int col = (mouseX - BOARDSTART_X - (int)background.posX) / TILE;
    int row = (mouseY - BOARDSTART_Y) / TILE;

    if (col < 0 || col >= BOARD_SIZE || row < 0 || row >= BOARD_SIZE) {
        return {-1, -1};
    }

    return {col, row};
}

extern Game * game;

// void PieceCtrl::ProcessAITurn() {   이미 플레이어 턴이면 아무것도 하지 않음 	if (Turn != AI) {
// return; 	}   AI 기물이 있는지 확인 	bool aiPieceFound = false; 	for (int row = 0; row
// < BOARD_SIZE; ++row) { 		for (int col = 0; col < BOARD_SIZE; ++col) { Piece*
// piece = boardctrl.getPiece(row, col); 			if (piece && piece->getAlive() &&
// piece->getOwner() == AI) { 				aiPieceFound = true; 하나라도 찾으면 루프 종료 				break;
// } 		} 		if (aiPieceFound) break; 	} 	if (!aiPieceFound) { 	  AI 기물이 없으면 턴만 넘김
// Turn = PLAYER; 		return; 	}   여기서부터는 AI 기물이 있는 경우 	  간단한 테스트 이동 시도 	for (int
// row = 0; row < BOARD_SIZE; ++row) { for (int col = 0; col < BOARD_SIZE;
// ++col) { 			Piece* piece = boardctrl.getPiece(row, col); 			if (piece &&
// piece->getAlive() && piece->getOwner() == AI) {
// std::vector<std::pair<int, int>> moves = piece->getLegalMoves(&boardctrl);
// if (!moves.empty()) { 					int toRow = moves[0].first; 					int toCol =
// moves[0].second; 					bool success = Move(row, col, toRow, toCol); 					if
// (success) { 						Turn = PLAYER; return; 					} 				} 			} 		} 	}   모든 AI 기물이
// 움직일 수 없는 경우 	Turn = PLAYER; } void PieceCtrl::ProcessAITurn() { 	if (Turn ==
// AI) { 	  테스트: 간단한 이동 시도 (예: 폰을 한 칸 앞으로) 		bool success = Move(6, 0, 5, 0);  첫
// 번째 폰을 한 칸 앞으로 		if (success) { Turn = PLAYER; 		} 	} } void
// PieceCtrl::ForceAIMove() {      간단한 테스트 이동 (예: 첫 번째 AI 폰을 한 칸 앞으로) bool moved
// = false;      첫 번째 AI 폰 찾기     for (int col = 0; col < BOARD_SIZE && !moved;
// ++col) {         Piece* pawn = boardctrl.getPiece(1, col);  AI 폰은 1행에 있을 것
// if (pawn && pawn->getAlive() && pawn->getOwner() == AI) { 한 칸 앞으로 이동 시도
// moved = Move(1, col, 2, col);             break; }     }      폰 이동이 안 되면 다른
// 기물 시도     if (!moved) {         for (int col = 0; col < BOARD_SIZE && !moved;
// ++col) {             Piece* piece = boardctrl.getPiece(0, col);  AI 기물은 0행에
// 있을 것             if (piece && piece->getAlive() && piece->getOwner() == AI) {
// 나이트라면 앞으로 이동 시도                 if (col == 1 || col == 6) {  나이트 위치 moved =
// Move(0, col, 2, col == 1 ? 0 : 7);                 }             } }     } }