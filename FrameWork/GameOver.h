#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "Include.h"

class GameOver
{
	Sprite playerLose;
	Sprite playerWin;

public:
	GameOver();
	~GameOver();

	float loseAlpha;
	float winAlpha;

	void Init();
	void Draw();
	void Update_PLWin(double frame);
	void Update_PLLose(double frame);
};

#endif