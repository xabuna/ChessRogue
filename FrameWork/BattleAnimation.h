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

	DWORD m_AtkAniTime;	//�ִϸ��̼� Ÿ�̸�
	float rot;			//�ִϸ��̼� Ÿ�̸� ������ ����

	void Init();
	void Update();
	void Draw();
};

#endif