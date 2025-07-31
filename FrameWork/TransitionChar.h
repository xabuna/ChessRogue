#ifndef _TRANSITIONCHAR_H_
#define _TRANSITIONCHAR_H_

#include "Include.h"

class TransitionChar
{
	Sprite PlayerChar[6];
	Sprite AIChar[6];
public:
	TransitionChar();
	~TransitionChar();
	
	float playerX, playerY;
	float aiX, aiY;

	float speed;
	int charAlpha;
	bool charFadeIn;

	void Init();
	void Draw(PieceType piecePL, PieceType pieceAI);
	void Update(double frame);

	void Start();
	void Stop();
};

extern TransitionChar transitionChar;

#endif
