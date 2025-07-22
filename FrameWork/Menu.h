#ifndef __Menu_H__
#define __Menu_H__

class Logo;

class Menu : public Chap
{
	HWND m_hWnd;

	Sprite logo_game;
	Sprite background_obj;

	Sprite start_btn;
	Sprite option_btn;
	Sprite quit_btn;

	Sprite clicker;

public:
	Menu();
	~Menu();
	
	int clickerY;
	int clicker_list[3] = { 580, 700, 820 };
	int list_num;
	int alpha_gamelogo;
	int alpha_menu;

	bool fadein_gamelogo = false;
	bool active_menu = false;

	float speed = 2000.0f;

	RECT btn_box[3] = {
		{ 240, 580, 240 + 460, 580 + 120 },  // Start
		{ 240, 700, 240 + 460, 700 + 120 },  // Option
		{ 240, 820, 240 + 460, 820 + 120 }   // Quit
	};

	RECT start_box, option_box, quit_box;

	virtual void Init(HWND m_hwnd);
	virtual void Update(double frame);
	virtual void Draw();

	virtual void OnMessage(MSG* msg);

};

#endif