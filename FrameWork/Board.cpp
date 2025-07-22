#include "Board.h"

Board board;

Board::Board() {}

//Board::Board(HWND hWnd)
//	:x(0), y(0),m_hWnd(hWnd) {
//}

Board::~Board()
{

}

void Board::Init()
{
	char FileName[256];

	sprintf_s(FileName, "./resource/Img/chess/UI/chessBoard_back.png");
	BoardBackimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/UI/chessBoard.png");
	Boardimg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}

//void Board::WinInit()
//{
//	InvalidateRect(m_hWnd, NULL, TRUE);
//	UpdateWindow(m_hWnd);
//
//	// 보드 기물 초기화 
//	for (int row = 0; row < 8; row++)
//		for (int col = 0; col < 8; col++)
//		{
//			this->board[row][col] = 0;
//		}
//	
//	// 윈도우 클라이언트 영역의 디스플레이 디바이스 컨텍스트(DC) 핸들을 구해서 반환해서 대입..
//	HDC hDC = GetDC(m_hWnd);
//
//	HPEN hPen, hOldPen;
//
//	hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
//	// 펜을 디바이스 컨텍스트에 넣고 반환된 전에 펜 핸들을 대입.
//	hOldPen = (HPEN)SelectObject(hDC, hPen);
//
//	for (int row = 0; row < 8; row++)
//		for (int col = 0; col < 8; col++)
//		{
//			x = 400 + col * 110;
//			y = 80 + row * 110;
//
//			Rectangle(hDC, x, y, x + 110, y + 110);
//		}
//
//	// 펜을 디바이스 컨텍스트에 넣는다.
//	SelectObject(hDC, hOldPen);
//
//	// 펜, 브러쉬 객체를 삭제한다.
//	DeleteObject(hPen);
//
//	// 디바이스 컨텍스트를 반납한다.
//	ReleaseDC(m_hWnd, hDC);
//}

void Board::Update()
{
	
}

void Board::Draw()
{

	if (Gmanager.m_GameStart == true)
	{
		BoardBackimg.SetColor(255, 255, 255, 255);
		BoardBackimg.Draw(367 + background.posX, 47);

		Boardimg.SetColor(255, 255, 255, 255);
		//처음 그려지는 위치
		Boardimg.Draw(400 + background.posX, 80);
		/* IMAGE[Index].Render(x 좌표,y 좌표,방향변수(이미지의 회전),x 사이즈,y사이즈,중심점); */
	}
}

/*
	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, 50, 50, 150, 150);
	SelectObject(hdc, hOldBrush2);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
*/