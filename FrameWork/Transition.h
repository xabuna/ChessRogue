#ifndef _TRANSITION_H_
#define _TRANSITION_H_

#include "Include.h"

class Transition
{
private:
	Sprite BackTransition;
	Sprite WarpTransition[6];

public:
	Transition();
	~Transition();

	float warpX, warpY;

	float m_framecnt;

	bool active;
	bool scrollRight = ON;

	DWORD m_WarpTime;	//�ִϸ��̼� Ÿ�̸�
	float rot;			//�ִϸ��̼� Ÿ�̸� ������ ����

	void TranActive();
	void Init();
	void Draw(PieceType pieceAI);
	void Update();
};

extern Transition transition;

#endif