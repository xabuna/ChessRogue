#include "Include.h"


Over::Over()
{
}

Over::~Over()
{
}

void Over::Init(HWND m_hWnd)
{
	this->m_hWnd = m_hWnd;
}

// Chap, 재정의 함수 호출
void Over::Update(double frame)
{
	//if(처리 후) g_Mng.n_Chap = MENU; 
}

void Over::Draw()
{
	
}

void Over::OnMessage( MSG* msg )
{

}