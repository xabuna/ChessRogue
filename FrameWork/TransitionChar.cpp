#include "TransitionChar.h"

TransitionChar transitionChar;

TransitionChar::TransitionChar() {
	playerX = -255;
	playerY = 255;
	aiX = 1150+255;
	aiY = 255;
	speed = 2000.0f;
	charAlpha = 0;
	charFadeIn = OFF;
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
	if (charFadeIn == OFF)
		return;

	PlayerChar[piecePL-1].SetColor(255, 255, 255, charAlpha);
	PlayerChar[piecePL-1].Draw(playerX, playerY);

	AIChar[pieceAI-1].SetColor(255, 255, 255, charAlpha);
	AIChar[pieceAI-1].Draw(aiX, aiY);
}

void TransitionChar::Update(double frame)
{
	//OutputDebugStringA("[TransitionChar] Update() 호출됨\n");

	if (!charFadeIn) {
		//OutputDebugStringA("[TransitionChar] charFadeIn == false. 리턴\n");
		return;
	}

	char buf[128];
	sprintf_s(buf, "[TransitionChar] frame=%.4f, alpha=%d, charAlpha=%d, playerX=%d, aiX=%d\n",
		frame, (int)(speed * frame / 1000), charAlpha, playerX, aiX);
	//OutputDebugStringA(buf);

	float alpha = speed * frame / 1000;
	float charstat = speed * frame / 1000;

	charAlpha += (int)alpha;
	playerX += (int)charstat;
	aiX -= (int)charstat;

	if (charAlpha >= 255 && playerX >= 0 && aiX <= 1150)
	{
		charAlpha = 255;
		playerX = 0;
		aiX = 1150;
	}

	if (!transition.active)
	{
		charFadeIn = false; // 이거 안 꺼지면 무한 루프
		//OutputDebugStringA("[TransitionChar] 트랜지션 완료됨 → charFadeIn = false 전환\n");
	}
}

void TransitionChar::Start() {
	charFadeIn = ON;
	charAlpha = 0;
	playerX = -255;
	aiX = 1150 + 255;

	//OutputDebugStringA("[TransitionChar] Start() 호출됨: charFadeIn=1\n");
}

void TransitionChar::Stop() {
	charFadeIn = OFF;
	//OutputDebugStringA("[TransitionChar] Stop() 호출됨: charFadeIn=0\n");
}