#ifndef _MAP_H_
#define _MAP_H_

#include "Include.h"

class Map
{
	DWORD tranStartTime;
	DWORD tranDuration;
public :
	Map();
	~Map();
	
	Sprite m_fieldBoard;
	Sprite m_fieldBattle;

	Sprite m_field_IMAGE[10];//그냥 여유있게

	//int m_Stage;

	//Sprite m_MapImg1_1[6];
	//DWORD m_MapImg1_1_ani1;
	//int m_MapImg1_1_ani1Count;

	double posX, posY;
	double targetStageX, targetStageY;
	float scrollSpeed;

	bool cameraMove = OFF;

	void Init();
	void StartTransition();
	void Update(double frame);
	void Draw();
};

extern Map background;

#endif