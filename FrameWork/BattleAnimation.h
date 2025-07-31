#ifndef _BATTLEANIMATION_H_
#define _BATTLEANIMATION_H_

#include "Include.h"

class AttackAni
{
	Sprite ForkAct_WP;
	

public:
	AttackAni();
	~AttackAni();

	float x, y;	
	int m_framecnt;

	DWORD m_AtkAniTime;	//애니메이션 타이머
	float rot;			//애니메이션 타이머 딜레이 변수

	void Init();
	void Update();
	void Draw();
};

#endif