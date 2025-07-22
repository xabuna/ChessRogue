#include "Include.h"

Map background;


Map::Map()
{
	//m_Stage = 1;

	posX = 0;
	posY = 0;
	targetStageX = 0;
	targetStageY = 0;
	
	scrollSpeed = 100.0f;
	tranStartTime = 0;
	tranDuration = 3000;
}

Map::~Map()
{
}

void Map::Init()
{
	//int i,j;
	char FileName[256];
	

	sprintf_s(FileName, "./resource/Img/chess/map/background.png");
	m_fieldBoard.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/map/background_menu.png");
	m_fieldBattle.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	//Loadfield(m_Stage);


}

//void Map::Loadfield(int stage)
//{
//	m_Stage = stage;
//}

void Map::StartTransition()
{
	transition.TranActive();  // Transition 클래스를 활성화
	tranStartTime = GetTickCount64();  // 트랜지션 시작 시간 기록
}

void Map::Update(double frame)
{
	float scrolling = (float)(frame / 10.0f);

	//char buf[256];
	//sprintf_s(buf, "frame: %.2f, scrolling: %.2f, posX: %.2f, targetStageX: %.2f\n", frame, scrolling, posX, targetStageX);
	//OutputDebugStringA(buf);


	if (fabs(posX - targetStageX) > 1.0f)
	{
		if (posX < targetStageX)
		{
			posX += scrollSpeed * scrolling;
			if (posX > targetStageX)
			{
				posX = targetStageX;
			}
		}

		else if (posX > targetStageX)
		{
			posX -= scrollSpeed * scrolling;
			if (posX < targetStageX)
			{
				posX = targetStageX;
			}
		}
	}


	if (transition.active && GetTickCount64() - tranStartTime >= tranDuration)
	{
		transition.active = OFF;  // 트랜지션 종료
		posX = targetStageX;
		return;
	}
}

void Map::Draw()
{
	m_fieldBoard.Render(posX, posY, 0, 1, 1);
	m_fieldBattle.Render(posX + 1680, posY, 0, 1, 1);
}

//Draw에서 애니메이션 배경
/*for(i = 0; i<6; i++ )
{
	sprintf_s(FileName, "./resource/Img/map1/BG_Hades_1/BG_Hades_%04d.tga", i + 1);
	m_MapImg1_1[i].Create( FileName ,false,D3DCOLOR_XRGB(0,0,0));

}*/

/*if(GetTickCount64() - m_MapImg1_1_ani1 > frame)
{
	if(m_Stage==1)
	{
		m_MapImg1_1_ani1Count++;
		if(m_MapImg1_1_ani1Count > 44) m_MapImg1_1_ani1Count = 0;
	}

	m_MapImg1_1_ani1 = GetTickCount64();
}*/

//Update에서 애니메이션 배경
 		//m_MapImg1_1[0].Render(posX, posY, 0, 1, 1);
		//m_MapImg1_1[1].Render(posX, posY, 0, 1, 1);
		//m_MapImg1_1[3].Render(posX+270, posY+70, 0, 1, 1);
		//m_MapImg1_2[m_MapImg1_1_ani1Count].Render(posX, posY, 0, 1.5, 1.5);
		//m_MapImg1_1[2].Render(posX+190, posY, 0, 1, 1);
		//m_MapImg1_1[4].Render(posX+900, posY, 0, 1, 1);
		//m_MapImg1_1[5].Render(posX, posY, 0, 1, 1);
