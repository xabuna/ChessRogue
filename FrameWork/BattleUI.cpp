#include "BattleUI.h"	
#include <algorithm>
#define CLAMP(val, minVal, maxVal) ((val) < (minVal) ? (minVal) : ((val) > (maxVal) ? (maxVal) : (val)))

BattleUI battleUI;

BattleUI::BattleUI() {

	pl_platX = -500.0f;
	ai_platX = 500.0f;
	btnY = 1050.0f;
	speed = 2000.0f;
	battlePhase = OFF;
	btnRaise = OFF;
}

BattleUI::~BattleUI() {

}


void BattleUI::Init() {

	char FileName[256];

	for (int i = 0; i < 6; ++i)
	{
		sprintf_s(FileName, "./resource/Img/chess/Battlepiece/battle_PL_%02d.png", i + 1);
		Wh_piece[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int j = 0; j < 6; ++j)
	{
		sprintf_s(FileName, "./resource/Img/chess/Battlepiece/battle_AI_%02d.png", j + 1);
		Bk_piece[j].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	sprintf_s(FileName, "./resource/Img/chess/battleUIsprite/button_atk.png");
	AtkBox.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/battleUIsprite/button_def.png");
	DefBox.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/battleUIsprite/button_item.png");
	ItemBox.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	//======================================= HP =======================================//
	sprintf_s(FileName, "./resource/Img/chess/battleUI/pl_HPbar.png");
	pl_HPbar.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/battleUI/pl_HPempty.png");
	pl_HPempty.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/battleUI/pl_HPbarback.png");
	pl_HPbarback.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/battleUI/ai_HPbar.png");
	ai_HPbar.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/battleUI/ai_HPempty.png");
	ai_HPempty.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/chess/battleUI/ai_HPbarback.png");
	ai_HPbarback.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));


	InitButtons();
}

void BattleUI::Draw(HDC hdc, PieceType piecePL,PieceType pieceAI) {

	if (battlePhase == OFF)
		return;



	Wh_piece[piecePL - 1].SetColor(255, 255, 255, 255);
	Wh_piece[piecePL - 1].Draw(pl_platX, 0);

	Bk_piece[pieceAI - 1].SetColor(255, 255, 255, 255);
	Bk_piece[pieceAI - 1].Draw(ai_platX, 0);

	///////////////////////////////////////////////////////////////////////////위치같음
	pl_HPempty.SetColor(255, 255, 255, 255);  // 색상 변경
	pl_HPempty.Draw(970, 510);  //이미지출력

	pl_HPbar.SetColor(255, 255, 255, 255);  // 색상 변경
	pl_HPbar.Render(1680, 510, 0, -currentHPPlayerRatio, 1, 0);
	///////////////////////////////////////////////////////////////////////////
	pl_HPbarback.SetColor(255, 255, 255, 255);  // 색상 변경
	pl_HPbarback.Draw(900, 510);  //이미지출력

	///////////////////////////////////////////////////////////////////////////위치같음
	ai_HPempty.SetColor(255, 255, 255, 255);  // 색상 변경
	ai_HPempty.Draw(0, 125);  //이미지출력

	ai_HPbar.SetColor(255, 255, 255, 255);  // 색상 변경
	ai_HPbar.Render(0, 125, 0, currentHPEnemyRatio, 1, 0);
	///////////////////////////////////////////////////////////////////////////
	ai_HPbarback.SetColor(255, 255, 255, 255);  // 색상 변경
	ai_HPbarback.Draw(0, 125);  //이미지출력

	AtkBox.SetColor(255, 255, 255, 255);  // 색상 변경
	AtkBox.Draw(0, btnY);  //이미지출력

	DefBox.SetColor(255, 255, 255, 255);  // 색상 변경
	DefBox.Draw(1100, btnY);  //이미지출력

	ItemBox.SetColor(255, 255, 255, 255);  // 색상 변경
	ItemBox.Draw(655, btnY);  //이미지출력

	// 메시지 출력 (DrawText 함수 사용)
	if (!currentMessage.empty() && messageTimer > 0.0f) {
		// WinAPI DrawText 예시 (적절히 위치 조정 필요)
		RECT rcText = { 1180, 600, 1680, 780 };  // 화면 하단 중앙 영역 설정 (가로 1920기준)
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);
		DrawTextA(hdc, currentMessage.c_str(), -1, &rcText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	DrawHPBar(hdc);
}

void BattleUI::battleStart()
{
	battlePhase = ON;
	btnRaise = OFF;
	pl_platX = -500.0f;
	ai_platX = 500.0f;
	btnY = 1050.0f + 832.0f;

}

void BattleUI::battleEnd()
{
	battlePhase = OFF;
}

void BattleUI::UpdatePiece(double frame) {
	if (battlePhase == OFF)
		return;

	float platformState = speed * frame / 500;

	// 보간 계산
	const float threshold = 0.001f;
	const float lerpSpeed = hpLerpSpeed * (float)frame;

	if (fabs(displayHPPlayerRatio - currentHPPlayerRatio) > threshold)
		displayHPPlayerRatio += (currentHPPlayerRatio - displayHPPlayerRatio) * lerpSpeed;
	else
		displayHPPlayerRatio = currentHPPlayerRatio;

	if (fabs(displayHPEnemyRatio - currentHPEnemyRatio) > threshold)
		displayHPEnemyRatio += (currentHPEnemyRatio - displayHPEnemyRatio) * lerpSpeed;
	else
		displayHPEnemyRatio = currentHPEnemyRatio;

	// 플랫폼 이동
	pl_platX += (int)platformState;
	ai_platX -= (int)platformState;

	if (pl_platX >= 0 && ai_platX <= 0) {
		pl_platX = 0;
		ai_platX = 0;
		btnRaise = ON;
	}
}

void BattleUI::UpdateBtn(double frame)
{
	if (btnRaise == OFF)
		return;

	float btnState = speed * frame / 300;

	btnY -= (int)btnState;

	if (btnY <= 832)
	{
		btnY = 832;
	}



}

void BattleUI::InitButtons() {

	buttons.clear();

	buttons.push_back({ {0, 832, 580, 1050}, BattleButtonType::ATTACK });
	buttons.push_back({ {1100, 832, 1680, 1050}, BattleButtonType::DEFEND });
	buttons.push_back({ {655, 832, 1025, 1050}, BattleButtonType::USEITEM });
}

void BattleUI::HandleClick(int mx, int my) {

	if (battlePhase == OFF)
		return;

	for (const auto& btn : buttons) {
		if (PtInRect(&btn.rect, POINT{ mx, my })) {
			switch (btn.type) {
			case BattleButtonType::ATTACK:
				BattleManager::GetInstance().PlayerAttack();
				break;
			case BattleButtonType::DEFEND:
				BattleManager::GetInstance().PlayerDefend();
				break;
			case BattleButtonType::USEITEM:
				BattleManager::GetInstance().UseItem();
				break;
			}
			break; // 한 번만 실행
		}
	}
}

void BattleUI::SetMessage(const std::string& msg, float duration) {
	currentMessage = msg;
	messageTimer = duration;
}

void BattleUI::UpdateMessage(double deltaTime) {
	if (messageTimer > 0.0f) {
		messageTimer -= (float)deltaTime;
		if (messageTimer <= 0.0f) {
			messageTimer = 0.0f;
			currentMessage.clear();
		}
	}
}

void BattleUI::SetHP(int playerHP, int playerMaxHP, int enemyHP, int enemyMaxHP) {
    currentHPPlayer = playerHP;
    maxHPPlayer = playerMaxHP;
    currentHPEnemy = enemyHP;
    maxHPEnemy = enemyMaxHP;

    // 체력 비율 계산 (0.0 ~ 1.0), 최대 체력이 0이 되는 예외 방지
    currentHPPlayerRatio = (maxHPPlayer > 0) ? (float)currentHPPlayer / maxHPPlayer : 0.0f;
    currentHPEnemyRatio = (maxHPEnemy > 0) ? (float)currentHPEnemy / maxHPEnemy : 0.0f;

    // 디버깅 출력
    char buf[128];
    sprintf_s(buf, "[BattleUI::SetHP] Player: %d/%d (%.2f), Enemy: %d/%d (%.2f)\n",
        currentHPPlayer, maxHPPlayer, currentHPPlayerRatio,	
        currentHPEnemy, maxHPEnemy, currentHPEnemyRatio);
    OutputDebugStringA(buf);
}


void BattleUI::DrawHPBar(HDC hdc) {
	// 백 바
	pl_HPbarback.SetColor(255, 255, 255, 255);
	pl_HPbarback.Draw((float)playerHPBarRect.left, (float)playerHPBarRect.top);

	ai_HPbarback.SetColor(255, 255, 255, 255);
	ai_HPbarback.Draw((float)enemyHPBarRect.left, (float)enemyHPBarRect.top);

	// 보간된 체력 비율로 클램핑 처리
	float playerFillRatio = CLAMP(displayHPPlayerRatio, 0.0f, 1.0f);
	float enemyFillRatio = CLAMP(displayHPEnemyRatio, 0.0f, 1.0f);

	pl_HPbar.SetColor(255, 255, 255, 255);
	pl_HPbar.Render((float)playerHPBarRect.left, (float)playerHPBarRect.top, 0, playerFillRatio, 1.0f, 0);

	ai_HPbar.SetColor(255, 255, 255, 255);
	ai_HPbar.Render((float)enemyHPBarRect.left, (float)enemyHPBarRect.top, 0, enemyFillRatio, 1.0f, 0);
}