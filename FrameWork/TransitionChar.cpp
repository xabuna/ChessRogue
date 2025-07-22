#include "Include.h"

TransitionChar::TransitionChar() {
	playerX = 0;
	playerY = 0;
	aiX = 0;
	aiY = 0;
	charAlpha = 0;
}

TransitionChar::~TransitionChar() {

}

void TransitionChar::Init()
{

	char FileName[256];

	for (int i = 0; i < 6; i++)
	{
		sprintf_s(FileName, "./resource/Img/chess/battlesprite/wh_type_%02d.png", i + 1);
		PlayerChar[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 6; i++)
	{
		sprintf_s(FileName, "./resource/Img/chess/battlesprite/bk_type_%02d.png", i + 1);
		AIChar[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
}

void TransitionChar::Draw(PieceType piecePL, PieceType pieceAI)
{
	PlayerChar[piecePL].SetColor(255, 255, 0, 255);
	PlayerChar[piecePL].Draw(500, 500, 20, 20, 40, 40, 0, 0);

	AIChar[pieceAI].SetColor(255, 255, 0, 255);
	AIChar[pieceAI].Draw(500, 500, 20, 20, 40, 40, 0, 0);
}

void TransitionChar::Update(double frame)
{
	float alpha = speed * frame / 1000;

	if (charFadeIn)
	{
		charAlpha += (int)alpha;
		if (charAlpha >= 255)
		{
			charAlpha = 255;
			charFadeIn = OFF;
		}
	}
}