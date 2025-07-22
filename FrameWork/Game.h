#ifndef __Game_H__
#define __Game_H__

enum class GamePhase { BOARD = 0, MOVE_CAMERA = 1 , BATTLE = 2, GAME_OVER = 3 };

class Game : public Chap
{
	HWND m_hWnd;
	GamePhase gamephase;

public:
	Game();
	~Game();

	DWORD GameTime;

	virtual void Init(HWND m_hWnd);
	virtual void Update(double frame);
	virtual void Draw();

	virtual void OnMessage(MSG* msg);

	void SetWindowHandle(HWND hWnd) { m_hWnd = hWnd; }
};

#endif