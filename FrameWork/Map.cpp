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
}

Map::~Map()
{
}

void Map::Init()
{
	char FileName[256];
	

	sprintf_s(FileName, "./resource/Img/chess/map/background.png");
	m_fieldBoard.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/map/back_battlefield.png");
	m_fieldBattle.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}

void Map::StartTransition()
{
	tranStartTime = GetTickCount64();
}

void Map::Update(double frame)
{
	char buf[128];
	sprintf_s(buf, "Map.Update: posX=%.2f targetX=%.2f active=%d\n", posX, targetStageX, transition.active);
	
	(buf);

	float scrolling = (float)(frame / 10.0f);

	if (fabs(posX - targetStageX) > 1.0f)
	{
		if (posX < targetStageX) 
		{
			posX += scrollSpeed * scrolling;
			if (posX > targetStageX) posX = targetStageX;
		}
		else 
		{
			posX -= scrollSpeed * scrolling;
			if (posX < targetStageX) posX = targetStageX;
		}
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
