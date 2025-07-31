//#include "include.h"
//
//Bird bird;
//
//Bird::Bird()
//{
//	x = 0;
//	y = 0;
//	m_BirdCount = 0;
//	m_BirdAniTime = 0;
//	rot = 0;
//}
//
//Bird::~Bird()
//{
//
//}
//
//void Bird::Init()
//{
//	char FileName[256];
//
//	for (int i = 0; i < 2; i++)
//	{
//		sprintf_s(FileName, "./resource/Img/AAA/bird_fly%02d.png", i + 1);
//		Bdimg[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
//	}
//}
//
//void Bird::Update()
//{
//	if (GetTickCount64() - m_BirdAniTime > 500)	//GetTickCount():게임을 켜고 나서부터 흐르는 시간 1000 = 1초
//	{
//		m_BirdCount++;
//		if (m_BirdCount > 1)	m_BirdCount = 0;
//		m_BirdAniTime = GetTickCount64();
//
//		
//	}
//
//	if (GetTickCount64() - m_BirdAniTime > 10)	//GetTickCount():게임을 켜고 나서부터 흐르는 시간 1000 = 1초
//	{
//		rot += 0.1f;
//		if (rot >= 6.0f) rot = 0;
//	}
//}
//
//void Bird::Draw()
//{
//	if (Gmanager.m_GameStart == true)
//	{
//		Bdimg[m_BirdCount].SetColor(255, 255, 255, 100);
//		//처음 그려지는 위치
//		Bdimg[m_BirdCount].Draw(100, 100);
//
//		Bdimg[m_BirdCount].SetColor(255, 255, 0, 255);
//		Bdimg[m_BirdCount].Draw(500, 500, 20, 20, 40, 40, 0, 0);
//
//		Bdimg[m_BirdCount].SetColor(0, 255, 0, 255);
//		Bdimg[m_BirdCount].Render(250, 250, rot, -2, 2, 1);
//
//		Bdimg[m_BirdCount].SetColor(0, 255, 0, 255);
//		Bdimg[m_BirdCount].Render(x, y, 0, 2*dir, 2, 1);
//		/* IMAGE[Index].Render(x 좌표,y 좌표,방향변수(이미지의 회전),x 사이즈,y사이즈,중심점); */
//	}
//}