#include "Include.h"

Transition transition;

Transition::Transition()
{
	warpX = 0;
	warpY = 530 / 2;
	active = OFF;
}
Transition::~Transition()
{

}

void Transition::Init()
{
	char FileName[256];

	for (int i = 0; i < 6; i++)
	{
		sprintf_s(FileName, "./resource/Img/chess/battleUIsprite/vs_%02d.png", i + 1);
		WarpTransition[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	sprintf_s(FileName, "./resource/Img/chess/battleUIsprite/background_vs.png");
	BackTransition.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}
void Transition::Draw(PieceType pieceAI) 
{
	if (!active)
		return;

	float scrollX = m_framecnt * 168.0f;
	WarpTransition[pieceAI].RenderDraw(warpX, warpY, scrollX, 0, scrollX + 1680, 530, 0, 1, 1);

	BackTransition.Render(0, 0, 0, 1, 1);
}


void Transition::TranActive() {
	active = ON;
	scrollRight = ON;
	m_framecnt = 0;
	m_WarpTime = GetTickCount64();
}

void Transition::Update()
{
	if (!active)
	{
		return;
	}

	if (GetTickCount64() - m_WarpTime > 10)	//GetTickCount():게임을 켜고 나서부터 흐르는 시간 1000 = 1초
	{
		m_WarpTime = GetTickCount64();

		if (scrollRight)
		{
			m_framecnt += 0.5f;

			if (m_framecnt >= 10.0f)
			{
				m_framecnt = 10.0f;
				scrollRight = OFF;
			}
		}
		else
		{
			m_framecnt -= 0.5f;

			if(m_framecnt <=0.0f)
			{
				m_framecnt = 0.0f;
				scrollRight = ON;
			}
		}
	}
}
