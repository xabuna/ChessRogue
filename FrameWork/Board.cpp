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
//	// ���� �⹰ �ʱ�ȭ 
//	for (int row = 0; row < 8; row++)
//		for (int col = 0; col < 8; col++)
//		{
//			this->board[row][col] = 0;
//		}
//	
//	// ������ Ŭ���̾�Ʈ ������ ���÷��� ����̽� ���ؽ�Ʈ(DC) �ڵ��� ���ؼ� ��ȯ�ؼ� ����..
//	HDC hDC = GetDC(m_hWnd);
//
//	HPEN hPen, hOldPen;
//
//	hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
//	// ���� ����̽� ���ؽ�Ʈ�� �ְ� ��ȯ�� ���� �� �ڵ��� ����.
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
//	// ���� ����̽� ���ؽ�Ʈ�� �ִ´�.
//	SelectObject(hDC, hOldPen);
//
//	// ��, �귯�� ��ü�� �����Ѵ�.
//	DeleteObject(hPen);
//
//	// ����̽� ���ؽ�Ʈ�� �ݳ��Ѵ�.
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
		//ó�� �׷����� ��ġ
		Boardimg.Draw(400 + background.posX, 80);
		/* IMAGE[Index].Render(x ��ǥ,y ��ǥ,���⺯��(�̹����� ȸ��),x ������,y������,�߽���); */
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