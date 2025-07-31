#include "GameOver.h"

GameOver::GameOver() {
	loseAlpha = 0;
	winAlpha = 0;
}
GameOver::~GameOver() {

}

void GameOver::Init() {

	char FileName[256];

	sprintf_s(FileName, "./resource/Img/chess/UI/gameover.png");
	playerLose.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/UI/gamevictory.png");
	playerWin.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}
void GameOver::Draw() {

	playerLose.SetColor(255, 255, 255, loseAlpha);  // 색상 변경
	playerLose.Draw(0, 0);  //이미지출력

	playerWin.SetColor(255, 255, 255, winAlpha);  // 색상 변경
	playerWin.Draw(0, 0);  //이미지출력

}
void GameOver::Update_PLWin(double frame) {

}

void GameOver::Update_PLLose(double frame) {

}