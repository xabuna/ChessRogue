#include "BattleAnimation.h"

AttackAni attackAni;

AttackAni::AttackAni()
{
	x = 500.0; y = 500.0;
}

AttackAni::~AttackAni() {}

void AttackAni::Init()
{
	char FileName[256];
	sprintf_s(FileName, "./resource/Img/chess/Animation/forkAct_wp.png");
	ForkAct_WP.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

}

void AttackAni::Update()
{
	if (GetTickCount64() - m_AtkAniTime > 100)	//GetTickCount():게임을 켜고 나서부터 흐르는 시간 1000 = 1초
	{
		m_framecnt++;
		m_framecnt %= 8;
		m_AtkAniTime = GetTickCount64();
	}

}

void AttackAni::Draw()
{
	ForkAct_WP.RenderDraw(x, y, m_framecnt * 640, 0, (m_framecnt+1)*640, 640, 0, 0.5, 0.5);
}

extern AttackAni attackAni;