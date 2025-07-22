#include "Include.h"



Game::Game():gamephase(GamePhase::BOARD)
{
}

Game::~Game()
{
}

void Game::Init(HWND m_hWnd)
{
	this->m_hWnd = m_hWnd;

	background.Init();
	board.Init();

	boardctrl.Init();
	pieceCtrl.HighlightInit();

	transition.Init();

	boardUI.InvenInit();
	boardUI.BattlelogInit();

	Camera::GetInstance()->SetXCam(0);
	//coll.Init();
	//sound.Init();
	Gmanager.Init();
	// 데이타 베이스///////////////////
	sql.Init();
}

void Game::Draw()
{
	background.Draw();
	board.Draw();

	boardctrl.Draw();
	pieceCtrl.HighlightUpdate();

	boardUI.InvenDraw();
	boardUI.BattlelogDraw();

	transition.Draw(PIECE_PAWN);

	//coll.Draw();
	Gmanager.Draw();
	// 데이타 베이스///////////////////

	sql.Draw();
}

// Chap, 재정의 함수 호출
void Game::Update(double frame)
{
	//static int a = 0;
	//if(a == 0) 
	//{
	//	GameTime = GetTickCount();
	//	a = 1;
	//}
	static DWORD a = 0;

	transition.Update();

	switch (gamephase)
	{
	case GamePhase::BOARD:
	{
		if (!transition.active)
		{
			OutputDebugStringA("BOARD 호출되었는지 확인");
			background.Update(frame);
		}

		break;
	}
	case GamePhase::MOVE_CAMERA:
	{
		background.Update(frame);
		OutputDebugStringA("MOVE_CAMERA 호출");

		if (fabs(background.posX - background.targetStageX) >= 1.0f)
		{
				if (background.targetStageX == -1680)
				{	
					gamephase = GamePhase::BATTLE;
					OutputDebugStringA("BATTLE로 전환됨");
				}
				else if (background.targetStageX == 0)
				{
					gamephase = GamePhase::BOARD;
					OutputDebugStringA("BOARD로 전환됨");
				}
		}
		break;
	}
	case GamePhase::BATTLE:
	{
		if(transition.active)
		{
			OutputDebugStringA("BATTLE 호출되었는지 확인");
			background.Update(frame);
		}

		break;
	}
	case GamePhase::GAME_OVER:
	{
		//조건은 킹이 잡혔을 때
		//over.Update() 호출
		//over.Update()에서 화면 alpha=255 후 menu화면으로

		//backspace누르면 게임오버 보여주도록 하기
		break;
	}
	}

	if (GetTickCount64() - a > frame)
	{
		// 공부용
		Camera::GetInstance()->Update();
		key.Update();
		//player.Update();
		coll.Update();


        //===============================================================================================================================================
		//===============================================================================================================================================
		// AI 턴 처리
		//pieceCtrl.ProcessAITurn();

		if (pieceCtrl.GetTurn() == AI) {
			pieceCtrl.UpdateAITurnDelay();
		}

		// AI 턴 강제 처리 테스트용//
		// if (pieceCtrl.GetTurn() == AI) {
		// 	// 간단한 테스트 이동 (첫 번째 AI 폰을 한 칸 앞으로)
		// 	for (int col = 0; col < BOARD_SIZE; col++) {
		// 		Piece* piece = boardctrl.getPiece(1, col);
		// 		if (piece && piece->getOwner() == AI) {
		// 			// 한 칸 앞으로 이동 시도
		// 			bool success = pieceCtrl.Move(1, col, 2, col);
		// 			if (success) {
		// 				pieceCtrl.SwitchTurn(); // 턴 전환
		// 				break;
		// 			}
		// 		}
		// 	}
		// }
        //===============================================================================================================================================
        //===============================================================================================================================================
        //===============================================================================================================================================



		// 입 맛에 맞게

		//map.Update(130);
		Gmanager.Update();
		// 데이타 베이스///////////////////
		// 입 맛에 맞게 (여기선 안쓰임..프레임 값이 필요 할때만.. 그냥 방법만...)
		sql.Update(frame+3000);

		a = GetTickCount64();
	}

	POINT CursorPos;

	if (GetCursorPos(&CursorPos))
	{
		if (m_hWnd) {
			ScreenToClient(m_hWnd, &CursorPos);
		}

		int currentCursorX = CursorPos.x;
		int currentCursorY = CursorPos.y;

		pieceCtrl.HighlightFollow(currentCursorX, currentCursorY);
	}
	else
		pieceCtrl.HighlightFollow(-1, -1);

}



void Game::OnMessage( MSG* msg )
{
	if (msg->message == WM_KEYDOWN)
	{
		if (msg->wParam == VK_RETURN)
		{

			switch (gamephase)
			{
			case GamePhase::BOARD:

				background.targetStageX = -1680;
				background.StartTransition();
				gamephase = GamePhase::MOVE_CAMERA;
				break;

			case GamePhase::MOVE_CAMERA:

				break;

			case GamePhase::BATTLE:
				background.targetStageX = 0;
				gamephase = GamePhase::MOVE_CAMERA;
				break;
			}
		}
	}
}

