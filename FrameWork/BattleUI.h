#ifndef _BATTLEUI_H_
#define _BATTLEUI_H_

#define NOMINMAX
#include "Include.h"
#include <string>
#include <vector>
#include <algorithm>

struct BOX {
	float boxX, boxY;
};

enum class BattleButtonType {
    ATTACK,
    DEFEND,
    USEITEM
};

struct Button {
    RECT rect;
    BattleButtonType type;
};

class BattleUI
{

	Sprite Bk_piece[6];
	Sprite Wh_piece[6];

	Sprite pl_HPbar;
	Sprite pl_HPempty;
	Sprite pl_HPbarback;
	Sprite ai_HPbar;
	Sprite ai_HPempty;
	Sprite ai_HPbarback;


	Sprite AtkBox;
	Sprite DefBox;
	Sprite ItemBox;

	RECT playerHPBarRect = { 0, 125, 710, 165 };
	RECT enemyHPBarRect = { 0, 125, 780, 190 };



	int maxHPPlayer = 100;   // 최대 HP, 초기값 (init 때 업데이트)
	int maxHPEnemy = 100;

	int currentHPPlayer = 100;
	int currentHPEnemy = 100;

	// HP 바 Sprite
	Sprite HPBarBG;
	Sprite HPBarFill;

	// HP 상태값
	float currentHPPlayerRatio = 1.0f;
	float currentHPEnemyRatio = 1.0f;

	// 애니메이션용 현재 출력되는 체력 비율
	float displayHPPlayerRatio = 1.0f;
	float displayHPEnemyRatio = 1.0f;

	// 애니메이션 속도 계수 값이 크면 빨라짐
	const float hpLerpSpeed = 3.0f;


public:

	BOX box;

	BattleUI();
	~BattleUI();


	float pl_platX;
	float ai_platX;
	float btnY;
	float speed;

	bool battlePhase;
	bool btnRaise;

	void Init();
	void Draw(HDC hdc, PieceType attacker, PieceType defender);
	void UpdatePiece(double frame);
	void UpdateBtn(double frame);

	void SetHP(int playerHP, int playerMaxHP, int enemyHP, int enemyMaxHP);
	void DrawHPBar(HDC hdc);

	void battleStart();
	void battleEnd();

    std::vector<Button> buttons;	
    void InitButtons();          // 버튼 초기화 함수
	void HandleClick(int mx, int my);

    std::string currentMessage;      // 화면에 출력할 메시지
    float messageTimer = 0.0f;       // 메시지 지속 시간
    void SetMessage(const std::string& msg, float duration);
    void UpdateMessage(double deltaTime);
};
extern BattleUI battleUI;
#endif