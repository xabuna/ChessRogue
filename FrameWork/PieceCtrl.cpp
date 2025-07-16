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
	Highlight.Draw(highlightX, highlightY);

}

void PieceCtrl::HighlightUpdate() 
{

}
void PieceCtrl::HighlightFollow() 
{

}

void PieceCtrl::HighlightClear()
{
	pieceSelected = false;
	selectedCol = -1;
	selectedRow = -1;
	selectedPiece = nullptr;
}

//가독성을 위해 fromRow->mouseY로 바꾸라는 권유글이 있음->알아서하셈
//(준) mouseY도 좋긴하지만 여기서는 Handle 함수도 안 쓰고 Move 함수에는 이게 더 직관적으로 보여서 from로 쓰겠습니다
bool PieceCtrl::Move(int fromRow, int fromCol, int toRow, int toCol) {
	
	Piece* piece = boardctrl.getPiece(fromRow,fromCol); //참조
															//Piece* piece = board[fromRow][fromCol];

	if (!piece)	// 출발 위치에 기물이 없을 때
		return false; 

	// 1. getLegalMoves로 합법 이동 리스트 가져오기
	vector<pair<int, int>> legalMoves = piece->getLegalMoves(&boardctrl);

	// 2. 목적지가 legalMoves에 포함되는지 조사
	auto toMove = find(legalMoves.begin(), legalMoves.end(), make_pair(toRow, toCol)); // find 함수로 찾을 좌표 값을 구함 그래서 자료형 auto를 씀 vector 등 
																					   // begin 첫 번째 , end 마지막, make_pair -> vector에 int, int 한 쌍을 입력 (Input)
																					   // make_pair -> 이게 내가 가려고 하는 곳이 LegalMoves에 포함 되는지 
	if (toMove == legalMoves.end())
		return false; // '갈 곳'은 legal 이동 좌표가 아님

	// 3. 목적지에 적기물이 있다면 전투
	//Piece* target = board[toRow][toCol];
	//if (target) {
	//	if (target->getOwner() != piece->getOwner()) {
	//		// 전투 페이즈 새로 만들어서 초기화
	//		BattlePhase* battle = new BattlePhase(); // 동적할당 or 전역객체든
	//		battle->init(piece, target);             // 두 기물 넣어서 배틀 씬 시작
	//
	//		// 배틀 씬으로 화면 전환하는 신호 보내기
	//		// 예시: 상태머신, SceneController 등 쓰는 경우
	//		// GameManager::getInstance()->changeState(GameState::Battle);  // 이런 느낌
	//
	//		//  실제 배틀 씬으로 넘어간 뒤 update()로 턴제 전투 시작됨
	//
	//		return true; // 이동은 안 하고 전투 페이즈로 넘김
	//	}
	//	else {
	//		return false; // 아군 있으면 걍 안 움직임
	//	}
	//}

	// 4. 이동 처리

	boardctrl.setPiece(toRow, toCol, piece);
	boardctrl.setPiece(fromRow, fromCol, nullptr); 

	piece->setPosition(toRow, toCol);

	return true;
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
				SwitchTurn(); // 턴 전환 함수 (PLAYER ↔ AI)
			}


			// 하이라이트 지우기
			//clearHighlight();
		}
}

void PieceCtrl::SwitchTurn(){
	if			(Turn == AI)
					Turn = PLAYER;

	else if		(Turn == PLAYER)
					Turn = AI;

	else
					Turn = PLAYER;
}

POINT PieceCtrl::HandleMouseClick(int mouseY, int mouseX) {
	int col = ( mouseX - BOARDSTART_X ) / TILE;
	int row = ( mouseY - BOARDSTART_Y ) / TILE;
	return {col, row };
}