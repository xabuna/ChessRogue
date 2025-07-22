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
	// ����Ÿ ���̽�///////////////////
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
	// ����Ÿ ���̽�///////////////////

	sql.Draw();
}

// Chap, ������ �Լ� ȣ��
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
			OutputDebugStringA("BOARD ȣ��Ǿ����� Ȯ��");
			background.Update(frame);
		}

		break;
	}
	case GamePhase::MOVE_CAMERA:
	{
		background.Update(frame);
		OutputDebugStringA("MOVE_CAMERA ȣ��");

		if (fabs(background.posX - background.targetStageX) >= 1.0f)
		{
				if (background.targetStageX == -1680)
				{	
					gamephase = GamePhase::BATTLE;
					OutputDebugStringA("BATTLE�� ��ȯ��");
				}
				else if (background.targetStageX == 0)
				{
					gamephase = GamePhase::BOARD;
					OutputDebugStringA("BOARD�� ��ȯ��");
				}
		}
		break;
	}
	case GamePhase::BATTLE:
	{
		if(transition.active)
		{
			OutputDebugStringA("BATTLE ȣ��Ǿ����� Ȯ��");
			background.Update(frame);
		}

		break;
	}
	case GamePhase::GAME_OVER:
	{
		//������ ŷ�� ������ ��
		//over.Update() ȣ��
		//over.Update()���� ȭ�� alpha=255 �� menuȭ������

		//backspace������ ���ӿ��� �����ֵ��� �ϱ�
		break;
	}
	}

	if (GetTickCount64() - a > frame)
	{
		// ���ο�
		Camera::GetInstance()->Update();
		key.Update();
		//player.Update();
		coll.Update();


        //===============================================================================================================================================
		//===============================================================================================================================================
		// AI �� ó��
		//pieceCtrl.ProcessAITurn();

		if (pieceCtrl.GetTurn() == AI) {
			pieceCtrl.UpdateAITurnDelay();
		}

		// AI �� ���� ó�� �׽�Ʈ��//
		// if (pieceCtrl.GetTurn() == AI) {
		// 	// ������ �׽�Ʈ �̵� (ù ��° AI ���� �� ĭ ������)
		// 	for (int col = 0; col < BOARD_SIZE; col++) {
		// 		Piece* piece = boardctrl.getPiece(1, col);
		// 		if (piece && piece->getOwner() == AI) {
		// 			// �� ĭ ������ �̵� �õ�
		// 			bool success = pieceCtrl.Move(1, col, 2, col);
		// 			if (success) {
		// 				pieceCtrl.SwitchTurn(); // �� ��ȯ
		// 				break;
		// 			}
		// 		}
		// 	}
		// }
        //===============================================================================================================================================
        //===============================================================================================================================================
        //===============================================================================================================================================



		// �� ���� �°�

		//map.Update(130);
		Gmanager.Update();
		// ����Ÿ ���̽�///////////////////
		// �� ���� �°� (���⼱ �Ⱦ���..������ ���� �ʿ� �Ҷ���.. �׳� �����...)
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

