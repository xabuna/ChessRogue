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

	DWORD m_WarpTime;	//애니메이션 타이머
	float rot;			//애니메이션 타이머 딜레이 변수

	void TranActive();
	void Init();
	void Draw(PieceType pieceAI);
	void Update();
};

extern Transition transition;

#endif