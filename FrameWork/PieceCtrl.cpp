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
	//selectedPiece�� ��ġ�� �ʴ� ��쿡��
	if (currentRow != -1 && currentCol != -1)
	{
		// ���õ� ĭ�� Ŀ�� ĭ�� �ٸ� ���� Ŀ�� ���̶���Ʈ
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
        // AI �� ���۵� ���� ���
        aiWaiting = true;
        aiTurnStartTime = GetTickCount64();
        return;
    }

    DWORD now = GetTickCount64();
    if (now - aiTurnStartTime >= 700) {
        ProcessAITurn(); // 0.7�� �� ����
        aiWaiting = false;
    }
}

//�������� ���� fromRow->mouseY�� �ٲٶ�� �������� ����->�˾Ƽ��ϼ�
//(��) mouseY�� ���������� ���⼭�� Handle �Լ��� �� ���� Move �Լ����� �̰� �� ���������� ������ from�� ���ڽ��ϴ�
bool PieceCtrl::Move(int fromRow, int fromCol, int toRow, int toCol) {

	Piece* piece = boardctrl.getPiece(fromRow, fromCol); 

// 1. ��� ��ġ �⹰ Ȯ��
	if (!piece)	// ��� ��ġ�� �⹰�� ���� ��
		return false;

	// 2. getLegalMoves�� �չ� �̵� ����Ʈ ��������
   // Piece::getLegalMoves�� vector<pair<int, int>> (������ row, col)�� ��ȯ�Ѵٰ� ����
	vector<pair<int, int>> legalMoves = piece->getLegalMoves(&boardctrl);

	// 3. �������� legalMoves�� ���ԵǴ��� ����
	// find�� ����Ͽ� (toRow, toCol) ���� legalMoves�� �ִ��� Ȯ��
	auto toMove = find(legalMoves.begin(), legalMoves.end(), make_pair(toRow, toCol)); // find �Լ��� ã�� ��ǥ ���� ���� �׷��� �ڷ��� auto�� �� vector �� 
	// begin ù ��° , end ������, make_pair -> vector�� int, int �� ���� �Է� (Input)
	// make_pair -> �̰� ���� ������ �ϴ� ���� LegalMoves�� ���� �Ǵ��� 
	if (toMove == legalMoves.end())
		return false; // '�� ��'�� legal �̵� ��ǥ�� �ƴ�

	// 4. ���� ������ ó�� - ���߿� Ȱ��ȭ
	// ���⼭�� AI�� Ž������ �ٸ��� ���� ���� �÷��� �� ȣ��Ǵ� �Լ��̹Ƿ�
	// ���� ���� �⹰�� ���� UI/����/���� ������ ���� ���� ������ ���� ��.

	// Piece* target = board[toRow][toCol];
	// if (target) {
	// 	if (target->getOwner() != piece->getOwner()) {
	// 		// ���� ������ ���� ����
	// 		BattlePhase* battle = new BattlePhase(); // �����Ҵ� or ������ü��
	// 		battle->init(piece, target);             // �� �⹰ �־ ��Ʋ �� ����
	
	// 		// ��Ʋ ������ ȭ�� ��ȯ�ϴ� ��ȣ ������
	// 		// GameManager::getInstance()->changeState(GameState::Battle);  // �̷� ����
	
	// 		//  ���� ��Ʋ ������ �Ѿ �� update()�� ���� ���� ���۵�
	
	// 		return true; // �̵��� �� �ϰ� ���� ������� �ѱ�
	// 	}
	// 	else {
	// 		return false; // �Ʊ� ������ �� �� ������
	// 	}
	// }	

	// 5. ���� �⹰ �̵� ó��
	// �������� �⹰�� �־��µ� ������ �����ų�, �Ʊ� �⹰�̾��ٸ� ����� ���� �ʰ� ������ false �������� ����.
	// ���� ���⼭�� ��ĭ�̰ų� �� �⹰�� ������ ��Ȳ (���������� ��)�̶�� ����.

	/*======================================================================*/
	Piece* PieceTarget = boardctrl.getPiece(toRow, toCol);
	if (PieceTarget != nullptr) {
		// �� ���� ������ �⹰�� ������ ������ �־�� ��
		boardctrl.setPiece(toRow, toCol, nullptr); // �ϴ� ĭ�� ���
		delete PieceTarget; // �޸� ����

		// �̵� ���� �������� �ִ� �⹰�� nullptr�� ���� (���� �⹰�� ��� ����� �ϴ� �̸� ���� �⹰�� ���� �� �̵� �ϴ� ����)
		boardctrl.setPiece(toRow, toCol, piece);        // �⹰�� �� ��ġ�� �ű�
		boardctrl.setPiece(fromRow, fromCol, nullptr);  // ���� ��ġ�� �� ĭ���� ����
		piece->setPosition(toRow, toCol);               // �⹰ ��ü ������ ��ġ ���� ������Ʈ

		return true;                                    // �̵� ����
	}

	// �������� �� ĭ�� ��쿡�� �⹰ �̵� ó��
	boardctrl.setPiece(toRow, toCol, piece);        // �⹰�� �� ��ġ�� �ű�
	boardctrl.setPiece(fromRow, fromCol, nullptr);  // ���� ��ġ�� �� ĭ���� ����
	piece->setPosition(toRow, toCol);               // �⹰ ��ü ������ ��ġ ���� ������Ʈ

	return true;                                    // �̵� ����
}


// PieceCtrl::Move (const Move& move) <<< �����ε�� �Լ� (AI�� �ַ� ȣ���� �Լ�)
bool PieceCtrl::Move(const MoveLogic::Move& move){
    // Move ����ü���� from/to ������ �����Ͽ� ���� Move �Լ��� ȣ��
   // �̷��� �ϸ� ���� Move �Լ��� ������ ������ ���� ������ �� ����
    return Move(move.fromRow, move.fromCol, move.toRow, move.toCol);
}


void PieceCtrl::UpdatePos(Piece* piece, int toRow, int toCol) {
	piece->setPosition(toRow, toCol);
}

void PieceCtrl::Remove(int col, int row) {

	boardctrl.setPiece(row, col, nullptr);

	// ���� ���ŵ� �⹰�� �޸𸮸� �����ؾ� �Ѵٸ�
	// (��: �⹰�� ���� �Ҵ�Ǿ���, �� �̻� ������ ���� ��)
	// Piece* removedPiece = boardctrl.getPiece(row, col); // ���ŵǱ� �� �⹰ ��������
	// if (removedPiece) {
	//     delete removedPiece; // �޸� ����
	//     boardctrl.setPiece(row, col, nullptr); 
}

bool PieceCtrl::Promotable(Piece* piece) {
	return true;
}

void PieceCtrl::PieceMove(int fromRow, int fromCol)
{
	POINT pClick = HandleMouseClick(fromRow, fromCol);			
	
	if (pClick.x < 0 || pClick.x >= 8 || pClick.y < 0 || pClick.y >= 8)
		return; // ���� �� Ŭ���̸� �ƹ��͵� �� ��

								  
		if (!pieceSelected) {							 	    // �⹰�� ���õ��� �ʾ��� �� �� 
			
			selectedPiece = boardctrl.getPiece(pClick.y, pClick.x); // ����
			// 1�ܰ�: �⹰ ����	
			if (selectedPiece && selectedPiece->getOwner() == Turn)
			{												    // == Turn���� owner�� ���� ���� ���� ������ �� �ְ�
				selectedCol = pClick.x;
				selectedRow = pClick.y;
				pieceSelected = true;
			}
		}
		else {  // 2��° Ŭ���� �� �� �̹� �⹰�� ���� �Ǿ������ϱ� pieceSelected = true; �� else�� �̵�

			// 2�ܰ�: �⹰ �̵� �õ�

			bool success = Move(selectedRow, selectedCol, pClick.y, pClick.x);

			// �����̵� ���е� ���� �ʱ�ȭ
			pieceSelected = false;
			selectedCol = -1;
			selectedRow = -1;
			selectedPiece = nullptr;

			if (success) {
				// �̵� ���������� �� �ѱ��
				SwitchTurn();
				//ProcessAITurn(); // �� ��ȯ �Լ� (PLAYER �� AI)
			}


			// ���̶���Ʈ �����
			//clearHighlight();
		}
}

void PieceCtrl::SwitchTurn() {
    // ���� �ܼ��ϰ� �ϸ� �ٲٱ�
    Turn = (Turn == PLAYER) ? AI : PLAYER;
}

// void PieceCtrl::ProcessAITurn() {
// 	if (Turn == AI) {
// 		// �׽�Ʈ: ������ �̵� �õ� (��: ���� �� ĭ ������)
// 		bool success = Move(6, 0, 5, 0); // ù ��° ���� �� ĭ ������

// 		if (success) {
// 			Turn = PLAYER;
// 		}
// 	}
// }

void PieceCtrl::ProcessAITurn() {
	// ���� ���� AI�� �ƴ϶�� �ƹ��͵� ���� ���� (�߿�!)
	if (Turn != AI) {
		return;
	}

	OutputDebugStringA("ProcessAITurn �Լ� ȣ���: AI ��\n");

	IBoardEvaluator* evaluator = nullptr; // evaluator�� try/catch �ۿ��� ���� �� �ʱ�ȭ
	try {
		// AI ��ü ���� (�� �ϸ��� ���� ����)
		evaluator = new BasicMaterialEvaluator();
		ChessAI ai(evaluator);

		// AI���� ������ ���� ����ϵ��� ��û
		MoveLogic::Move bestMove = ai.GetBestMove(boardctrl);

		char moveDebugMsg[256]; // ����� �޽��� ����

		// 1. AI�� ��ȿ�� ���� ã�� ���ߴ��� Ȯ�� (GetBestMove���� -1, -1�� ��ȯ�ϴ� ���)
		if (bestMove.fromRow == -1 || bestMove.fromCol == -1 || bestMove.toRow == -1 || bestMove.toCol == -1) {
			OutputDebugStringA("AI: ��ȿ�� ���� ã�� ���� (GetBestMove ��ȯ�� ��ȿ)\n");
			Turn = PLAYER; // ��ȿ�� ���� �����Ƿ� ���� �÷��̾�� �ѱ�
			// evaluator�� finally ��� �Ǵ� �Ʒ����� ������ ��
			return; // �Լ� ����
		}

		// 2. AI�� ������ ���� ����
		bool success = Move(bestMove); // Move �Լ� ȣ��

		// ����� �޽��� ���
		sprintf_s(moveDebugMsg, "AI�� %d,%d -> %d,%d �̵� �õ�. ����: %s\n",
			bestMove.fromRow, bestMove.fromCol, bestMove.toRow, bestMove.toCol, success ? "��" : "�ƴϿ�");
		OutputDebugStringA(moveDebugMsg);

		// 3. �̵� ���� ���ο� ���� �� ��ȯ
		if (success) {
			OutputDebugStringA("AI �̵� ����! �� �÷��̾�� ��ȯ.\n");
			Turn = PLAYER; // �̵��� ���������� ���� �÷��̾�� �ѱ�
		}
		else {
			// �̵��� ������ ��� (��: �⹰�� �̹� �׾��ų�, �̵� �Լ��� ���� ������ ��ȯ�ϴ� ���)
			OutputDebugStringA("AI �̵� ���� ����! �� �÷��̾�� ��ȯ.\n");
			Turn = PLAYER; // �̵��� �����߾ ���� ���� ������ ���� ���� �ѱ�
		}
	}
	catch (const std::bad_alloc& e) { // �޸� �Ҵ� ���� ���� ó��
		char errorMsg[256];
		sprintf_s(errorMsg, "ProcessAITurn: �޸� �Ҵ� ���� - %s\n", e.what());
		OutputDebugStringA(errorMsg);
		Turn = PLAYER; // �� �ѱ�
	}
	catch (const std::exception& e) { // �ٸ� ǥ�� ���� ó��
		char errorMsg[256];
		sprintf_s(errorMsg, "ProcessAITurn: ���� �߻� - %s\n", e.what());
		OutputDebugStringA(errorMsg);
		Turn = PLAYER; // �� �ѱ�
	}
	catch (...) { // ��� ��ó�� ���� ���
		OutputDebugStringA("ProcessAITurn: �� �� ���� ���� �߻�!\n");
		Turn = PLAYER; // �� �ѱ�
	}

	// evaluator�� �׻� delete
	if (evaluator) {
		delete evaluator;
		evaluator = nullptr;
	}
}

// void PieceCtrl::ProcessAITurn() {
// 	// �̹� �÷��̾� ���̸� �ƹ��͵� ���� ����
// 	if (Turn != AI) {
// 		return;
// 	}

// 	// AI �⹰�� �ִ��� Ȯ��
// 	bool aiPieceFound = false;
// 	for (int row = 0; row < BOARD_SIZE; ++row) {
// 		for (int col = 0; col < BOARD_SIZE; ++col) {
// 			Piece* piece = boardctrl.getPiece(row, col);
// 			if (piece && piece->getAlive() && piece->getOwner() == AI) {
// 				aiPieceFound = true;
// 				// �ϳ��� ã���� ���� ����
// 				break;
// 			}
// 		}
// 		if (aiPieceFound) break;
// 	}

// 	if (!aiPieceFound) {
// 		// AI �⹰�� ������ �ϸ� �ѱ�
// 		Turn = PLAYER;
// 		return;
// 	}

// 	// ���⼭���ʹ� AI �⹰�� �ִ� ���
// 		// ������ �׽�Ʈ �̵� �õ�
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

// 	// ��� AI �⹰�� ������ �� ���� ���
// 	Turn = PLAYER;
// }

	void PieceCtrl::ForceAIMove() {
    // ������ �׽�Ʈ �̵� (��: ù ��° AI ���� �� ĭ ������)
    bool moved = false;
    
    // ù ��° AI �� ã��
    for (int col = 0; col < BOARD_SIZE && !moved; ++col) {
        Piece* pawn = boardctrl.getPiece(1, col); // AI ���� 1�࿡ ���� ��
        if (pawn && pawn->getAlive() && pawn->getOwner() == AI) {
            // �� ĭ ������ �̵� �õ�
            moved = Move(1, col, 2, col);
            break;
        }
    }
    
    // �� �̵��� �� �Ǹ� �ٸ� �⹰ �õ�
    if (!moved) {
        for (int col = 0; col < BOARD_SIZE && !moved; ++col) {
            Piece* piece = boardctrl.getPiece(0, col); // AI �⹰�� 0�࿡ ���� ��
            if (piece && piece->getAlive() && piece->getOwner() == AI) {
                // ����Ʈ��� ������ �̵� �õ�
                if (col == 1 || col == 6) { // ����Ʈ ��ġ
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