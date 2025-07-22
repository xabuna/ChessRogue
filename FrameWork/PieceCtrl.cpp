#include "PieceCtrl.h"

PieceCtrl pieceCtrl;

void PieceCtrl::HighlightInit() {

	char FileName[256];

	sprintf_s(FileName, "./resource/Img/chess/UIElm/highlight.png");
	Highlight.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}


void PieceCtrl::HighlightDraw(int _row, int _col) {

	if (_col < 0 || _col>7 || _row < 0 || _row>7)
	{
		return;
	}

	int highlightX = BOARDSTART_X + _col * TILE;
	int highlightY = BOARDSTART_Y + _row * TILE;

	Highlight.SetColor(255, 255, 255, 255);
	Highlight.Draw(highlightX + background.posX, highlightY);

}

void PieceCtrl::HighlightUpdate() 
{
	if (pieceSelected) {
		HighlightDraw(selectedRow,selectedCol);
	}
	//selectedPiece와 겹치지 않는 경우에만
	if (currentRow != -1 && currentCol != -1)
	{
		// 선택된 칸과 커서 칸이 다를 때만 커서 하이라이트
		if (!(pieceSelected && currentRow == selectedRow && currentCol == selectedCol))
		{
			HighlightDraw(currentRow + background.posX, currentCol);
		}
	}
}

void PieceCtrl::HighlightFollow(int currentX,int currentY) 
{
	POINT InBoard = HandleMouseClick(currentY, currentX);

	if (InBoard.x >= 0 && InBoard.x < 8 && InBoard.y >= 0 && InBoard.y < 8)
	{
		currentCol = InBoard.x + background.posX;
		currentRow = InBoard.y;
	}
	else
	{
		currentCol = -1;
		currentRow = -1;
	}
}

void PieceCtrl::HighlightClear()
{
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

//가독성을 위해 fromRow->mouseY로 바꾸라는 권유글이 있음->알아서하셈
//(준) mouseY도 좋긴하지만 여기서는 Handle 함수도 안 쓰고 Move 함수에는 이게 더 직관적으로 보여서 from로 쓰겠습니다
bool PieceCtrl::Move(int fromRow, int fromCol, int toRow, int toCol) {

	Piece* piece = boardctrl.getPiece(fromRow, fromCol); 

// 1. 출발 위치 기물 확인
	if (!piece)	// 출발 위치에 기물이 없을 때
		return false;

	// 2. getLegalMoves로 합법 이동 리스트 가져오기
   // Piece::getLegalMoves가 vector<pair<int, int>> (목적지 row, col)을 반환한다고 가정
	vector<pair<int, int>> legalMoves = piece->getLegalMoves(&boardctrl);

	// 3. 목적지가 legalMoves에 포함되는지 조사
	// find를 사용하여 (toRow, toCol) 쌍이 legalMoves에 있는지 확인
	auto toMove = find(legalMoves.begin(), legalMoves.end(), make_pair(toRow, toCol)); // find 함수로 찾을 좌표 값을 구함 그래서 자료형 auto를 씀 vector 등 
	// begin 첫 번째 , end 마지막, make_pair -> vector에 int, int 한 쌍을 입력 (Input)
	// make_pair -> 이게 내가 가려고 하는 곳이 LegalMoves에 포함 되는지 
	if (toMove == legalMoves.end())
		return false; // '갈 곳'은 legal 이동 좌표가 아님

	// 4. 전투 페이즈 처리 - 나중에 활성화
	// 여기서는 AI의 탐색과는 다르게 실제 게임 플레이 시 호출되는 함수이므로
	// 실제 잡힌 기물에 대한 UI/사운드/전투 페이즈 진입 등의 로직이 들어가야 함.

	// Piece* target = board[toRow][toCol];
	// if (target) {
	// 	if (target->getOwner() != piece->getOwner()) {
	// 		// 전투 페이즈 진입 로직
	// 		BattlePhase* battle = new BattlePhase(); // 동적할당 or 전역객체든
	// 		battle->init(piece, target);             // 두 기물 넣어서 배틀 씬 시작
	
	// 		// 배틀 씬으로 화면 전환하는 신호 보내기
	// 		// GameManager::getInstance()->changeState(GameState::Battle);  // 이런 느낌
	
	// 		//  실제 배틀 씬으로 넘어간 뒤 update()로 턴제 전투 시작됨
	
	// 		return true; // 이동은 안 하고 전투 페이즈로 넘김
	// 	}
	// 	else {
	// 		return false; // 아군 있으면 걍 안 움직임
	// 	}
	// }	

	// 5. 실제 기물 이동 처리
	// 목적지에 기물이 있었는데 전투가 없었거나, 아군 기물이었다면 여기로 오지 않고 위에서 false 리턴했을 것임.
	// 따라서 여기서는 빈칸이거나 적 기물이 잡히는 상황 (전투페이즈 후)이라고 가정.

	/*======================================================================*/
	Piece* PieceTarget = boardctrl.getPiece(toRow, toCol);
	if (PieceTarget != nullptr) {
		// 이 곳이 실제로 기물이 잡히는 로직이 있어야 함
		boardctrl.setPiece(toRow, toCol, nullptr); // 일단 칸을 비움
		delete PieceTarget; // 메모리 해제

		// 이동 전에 목적지에 있던 기물을 nullptr로 만듦 (만약 기물을 잡는 경우라면 일단 미리 잡힌 기물을 제거 후 이동 하는 로직)
		boardctrl.setPiece(toRow, toCol, piece);        // 기물을 새 위치로 옮김
		boardctrl.setPiece(fromRow, fromCol, nullptr);  // 기존 위치를 빈 칸으로 만듦
		piece->setPosition(toRow, toCol);               // 기물 객체 내부의 위치 정보 업데이트

		return true;                                    // 이동 성공
	}

	// 목적지가 빈 칸인 경우에도 기물 이동 처리
	boardctrl.setPiece(toRow, toCol, piece);        // 기물을 새 위치로 옮김
	boardctrl.setPiece(fromRow, fromCol, nullptr);  // 기존 위치를 빈 칸으로 만듦
	piece->setPosition(toRow, toCol);               // 기물 객체 내부의 위치 정보 업데이트

	return true;                                    // 이동 성공
}


// PieceCtrl::Move (const Move& move) <<< 오버로드된 함수 (AI가 주로 호출할 함수)
bool PieceCtrl::Move(const MoveLogic::Move& move){
    // Move 구조체에서 from/to 정보를 추출하여 기존 Move 함수를 호출
   // 이렇게 하면 기존 Move 함수의 복잡한 로직을 쉽게 재사용할 수 있음
    return Move(move.fromRow, move.fromCol, move.toRow, move.toCol);
}


void PieceCtrl::UpdatePos(Piece* piece, int toRow, int toCol) {
	piece->setPosition(toRow, toCol);
}

void PieceCtrl::Remove(int col, int row) {

	boardctrl.setPiece(row, col, nullptr);

	// 만약 제거된 기물의 메모리를 해제해야 한다면
	// (예: 기물이 동적 할당되었고, 더 이상 사용되지 않을 때)
	// Piece* removedPiece = boardctrl.getPiece(row, col); // 제거되기 전 기물 가져오기
	// if (removedPiece) {
	//     delete removedPiece; // 메모리 해제
	//     boardctrl.setPiece(row, col, nullptr); 
}

bool PieceCtrl::Promotable(Piece* piece) {
	return true;
}

void PieceCtrl::PieceMove(int fromRow, int fromCol)
{
	POINT pClick = HandleMouseClick(fromRow, fromCol);			
	
	if (pClick.x < 0 || pClick.x >= 8 || pClick.y < 0 || pClick.y >= 8)
		return; // 범위 밖 클릭이면 아무것도 안 함

								  
		if (!pieceSelected) {							 	    // 기물이 선택되지 않았을 때 참 
			
			selectedPiece = boardctrl.getPiece(pClick.y, pClick.x); // 참조
			// 1단계: 기물 선택	
			if (selectedPiece && selectedPiece->getOwner() == Turn)
			{												    // == Turn으로 owner와 같은 턴일 때만 움직일 수 있게
				selectedCol = pClick.x;
				selectedRow = pClick.y;
				pieceSelected = true;
			}
		}
		else {  // 2번째 클릭을 할 때 이미 기물이 선택 되어있으니까 pieceSelected = true; 라서 else로 이동

			// 2단계: 기물 이동 시도

			bool success = Move(selectedRow, selectedCol, pClick.y, pClick.x);

			// 성공이든 실패든 선택 초기화
			pieceSelected = false;
			selectedCol = -1;
			selectedRow = -1;
			selectedPiece = nullptr;

			if (success) {
				// 이동 성공했으면 턴 넘기기
				SwitchTurn();
				//ProcessAITurn(); // 턴 전환 함수 (PLAYER ↔ AI)
			}


			// 하이라이트 지우기
			//clearHighlight();
		}
}

void PieceCtrl::SwitchTurn() {
    // 정말 단순하게 턴만 바꾸기
    Turn = (Turn == PLAYER) ? AI : PLAYER;
}

// void PieceCtrl::ProcessAITurn() {
// 	if (Turn == AI) {
// 		// 테스트: 간단한 이동 시도 (예: 폰을 한 칸 앞으로)
// 		bool success = Move(6, 0, 5, 0); // 첫 번째 폰을 한 칸 앞으로

// 		if (success) {
// 			Turn = PLAYER;
// 		}
// 	}
// }

void PieceCtrl::ProcessAITurn() {
	// 현재 턴이 AI가 아니라면 아무것도 하지 않음 (중요!)
	if (Turn != AI) {
		return;
	}

	OutputDebugStringA("ProcessAITurn 함수 호출됨: AI 턴\n");

	IBoardEvaluator* evaluator = nullptr; // evaluator를 try/catch 밖에서 선언 및 초기화
	try {
		// AI 객체 생성 (매 턴마다 새로 생성)
		evaluator = new BasicMaterialEvaluator();
		ChessAI ai(evaluator);

		// AI에게 최적의 수를 계산하도록 요청
		MoveLogic::Move bestMove = ai.GetBestMove(boardctrl);

		char moveDebugMsg[256]; // 디버깅 메시지 버퍼

		// 1. AI가 유효한 수를 찾지 못했는지 확인 (GetBestMove에서 -1, -1을 반환하는 경우)
		if (bestMove.fromRow == -1 || bestMove.fromCol == -1 || bestMove.toRow == -1 || bestMove.toCol == -1) {
			OutputDebugStringA("AI: 유효한 수를 찾지 못함 (GetBestMove 반환값 무효)\n");
			Turn = PLAYER; // 유효한 수가 없으므로 턴을 플레이어에게 넘김
			// evaluator는 finally 블록 또는 아래에서 삭제될 것
			return; // 함수 종료
		}

		// 2. AI가 선택한 수를 실행
		bool success = Move(bestMove); // Move 함수 호출

		// 디버깅 메시지 출력
		sprintf_s(moveDebugMsg, "AI가 %d,%d -> %d,%d 이동 시도. 성공: %s\n",
			bestMove.fromRow, bestMove.fromCol, bestMove.toRow, bestMove.toCol, success ? "예" : "아니오");
		OutputDebugStringA(moveDebugMsg);

		// 3. 이동 성공 여부에 따라 턴 전환
		if (success) {
			OutputDebugStringA("AI 이동 성공! 턴 플레이어로 전환.\n");
			Turn = PLAYER; // 이동에 성공했으면 턴을 플레이어에게 넘김
		}
		else {
			// 이동에 실패한 경우 (예: 기물이 이미 죽었거나, 이동 함수가 실패 로직을 반환하는 경우)
			OutputDebugStringA("AI 이동 실행 실패! 턴 플레이어로 전환.\n");
			Turn = PLAYER; // 이동에 실패했어도 무한 루프 방지를 위해 턴을 넘김
		}
	}
	catch (const std::bad_alloc& e) { // 메모리 할당 실패 예외 처리
		char errorMsg[256];
		sprintf_s(errorMsg, "ProcessAITurn: 메모리 할당 실패 - %s\n", e.what());
		OutputDebugStringA(errorMsg);
		Turn = PLAYER; // 턴 넘김
	}
	catch (const std::exception& e) { // 다른 표준 예외 처리
		char errorMsg[256];
		sprintf_s(errorMsg, "ProcessAITurn: 예외 발생 - %s\n", e.what());
		OutputDebugStringA(errorMsg);
		Turn = PLAYER; // 턴 넘김
	}
	catch (...) { // 모든 미처리 예외 잡기
		OutputDebugStringA("ProcessAITurn: 알 수 없는 예외 발생!\n");
		Turn = PLAYER; // 턴 넘김
	}

	// evaluator는 항상 delete
	if (evaluator) {
		delete evaluator;
		evaluator = nullptr;
	}
}

// void PieceCtrl::ProcessAITurn() {
// 	// 이미 플레이어 턴이면 아무것도 하지 않음
// 	if (Turn != AI) {
// 		return;
// 	}

// 	// AI 기물이 있는지 확인
// 	bool aiPieceFound = false;
// 	for (int row = 0; row < BOARD_SIZE; ++row) {
// 		for (int col = 0; col < BOARD_SIZE; ++col) {
// 			Piece* piece = boardctrl.getPiece(row, col);
// 			if (piece && piece->getAlive() && piece->getOwner() == AI) {
// 				aiPieceFound = true;
// 				// 하나라도 찾으면 루프 종료
// 				break;
// 			}
// 		}
// 		if (aiPieceFound) break;
// 	}

// 	if (!aiPieceFound) {
// 		// AI 기물이 없으면 턴만 넘김
// 		Turn = PLAYER;
// 		return;
// 	}

// 	// 여기서부터는 AI 기물이 있는 경우
// 		// 간단한 테스트 이동 시도
// 	for (int row = 0; row < BOARD_SIZE; ++row) {
// 		for (int col = 0; col < BOARD_SIZE; ++col) {
// 			Piece* piece = boardctrl.getPiece(row, col);
// 			if (piece && piece->getAlive() && piece->getOwner() == AI) {
// 				std::vector<std::pair<int, int>> moves = piece->getLegalMoves(&boardctrl);
// 				if (!moves.empty()) {
// 					int toRow = moves[0].first;
// 					int toCol = moves[0].second;
// 					bool success = Move(row, col, toRow, toCol);
// 					if (success) {
// 						Turn = PLAYER;
// 						return;
// 					}
// 				}
// 			}
// 		}
// 	}

// 	// 모든 AI 기물이 움직일 수 없는 경우
// 	Turn = PLAYER;
// }

	void PieceCtrl::ForceAIMove() {
    // 간단한 테스트 이동 (예: 첫 번째 AI 폰을 한 칸 앞으로)
    bool moved = false;
    
    // 첫 번째 AI 폰 찾기
    for (int col = 0; col < BOARD_SIZE && !moved; ++col) {
        Piece* pawn = boardctrl.getPiece(1, col); // AI 폰은 1행에 있을 것
        if (pawn && pawn->getAlive() && pawn->getOwner() == AI) {
            // 한 칸 앞으로 이동 시도
            moved = Move(1, col, 2, col);
            break;
        }
    }
    
    // 폰 이동이 안 되면 다른 기물 시도
    if (!moved) {
        for (int col = 0; col < BOARD_SIZE && !moved; ++col) {
            Piece* piece = boardctrl.getPiece(0, col); // AI 기물은 0행에 있을 것
            if (piece && piece->getAlive() && piece->getOwner() == AI) {
                // 나이트라면 앞으로 이동 시도
                if (col == 1 || col == 6) { // 나이트 위치
                    moved = Move(0, col, 2, col == 1 ? 0 : 7);
                }
            }
        }
    }
}

POINT PieceCtrl::HandleMouseClick(int mouseY, int mouseX) {
	int col = ( mouseX - BOARDSTART_X ) / TILE + background.posX;
	int row = ( mouseY - BOARDSTART_Y ) / TILE + background.posX;
	return {col, row };
}