#pragma once
#include "Include.h"

class Map
{

public :
	Map();
	~Map();
	Sprite test;
	bool tests;
	/*Sprite m_MapImg1_1[6];
	Sprite m_MapImg1_2[45];*/
	Sprite m_MapImg1_1;

	//DWORD m_MapImg1_1_ani1;

	//int m_MapImg1_1_ani1Count;

	int m_Stage;

	double posX, posY;

	void Init();
	//void Update(double frame);
	void Update();
	void Draw();
};

extern Map map;