#include "Include.h"

static DWORD KeyTime = GetTickCount();
Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Init(HWND m_hWnd)
{

	this->m_hWnd = m_hWnd;

	alpha_gamelogo = 0;
	alpha_menu = 0;
	background_obj.Create("./resource/Img/chess/map/background_obj.png", false, D3DCOLOR_XRGB(0, 0, 0));
	logo_game.Create("./resource/Img/chess/UImenu/game_logo.png", false, D3DCOLOR_XRGB(0, 0, 0));
	start_btn.Create("./resource/Img/chess/UImenu/menu_start.png", false, D3DCOLOR_XRGB(0, 0, 0));
	option_btn.Create("./resource/Img/chess/UImenu/menu_option.png", false, D3DCOLOR_XRGB(0, 0, 0));
	quit_btn.Create("./resource/Img/chess/UImenu/menu_quit.png", false, D3DCOLOR_XRGB(0, 0, 0));
	clicker.Create("./resource/Img/chess/UImenu/menu_clicker.png", false, D3DCOLOR_XRGB(0, 0, 0));

	start_box = btn_box[0];
	option_box = btn_box[1];
	quit_box = btn_box[2];
}

// Chap, ������ �Լ� ȣ��
void Menu::Update(double frame)
{

	//key.Update();
	//if (xx.xxx > 100 * xxx.xxx)
	//{
	//	if (GetTickCount() - CoinTime > 100)
	//	{
	//		count++;
	//		CoinTime = GetTickCount();
	//	}
	//	if (count > 1) count = 0;
	//}
	float alpha = speed * frame / 1000;

	if (!fadein_gamelogo)
	{
		alpha_gamelogo += (int)alpha;
		if (alpha_gamelogo >= 255)
		{
			alpha_gamelogo = 255;
			alpha_menu = 255;
			active_menu = true;
			fadein_gamelogo = false;
		}
	}
	else if (active_menu)
	{
		if (list_num != -1)
		{
			clickerY = clicker_list[list_num];
		}
	}

}

void Menu::Draw()
{
	background_img.SetColor(255, 255, 255, 255);  // ���� ����
	background_img.Draw(0, 0);  //�̹������

	background_obj.SetColor(255, 255, 255, alpha_gamelogo);  // ���� ����
	background_obj.Draw(0, 0);  //�̹������

	start_btn.SetColor(255, 255, 255, alpha_menu);  // ���� ����
	start_btn.Draw(240, 580);  //�̹������

	option_btn.SetColor(255, 255, 255, alpha_menu);  // ���� ����
	option_btn.Draw(240, 700);  //�̹������

	quit_btn.SetColor(255, 255, 255, alpha_menu);  // ���� ����
	quit_btn.Draw(240, 820);  //�̹������

	clicker.SetColor(255, 255, 255, alpha_menu);
	clicker.Draw(120, clicker_list[list_num]-38); //clickY�� 542,662,782������ �׷����� ��.

	logo_game.SetColor(255, 255, 255, alpha_gamelogo);  // ���� ����
	logo_game.Draw(120, 180);  //�̹������


	//menuimg.Render(-50, 0, 0, 0.75, 0.75); //�̹������
	//dv_font.DrawString("�κ�", 200, 210);   //�������
	//if (GetTickCount() - AlTime > 100)
	//{
	//	alpha++;
	//	AlTime = GetTickCount();
	//}

	//if (alpha == 0) menuimg[2].SetColor(255, 255, 255, 255);
	//if (alpha == 1) menuimg[2].SetColor(255, 255, 255, 0);

	//if (xxx.xxx == 0) menuimg[2].Draw(407, 336);
	//else if (count < 2) menuimg[count].Draw(412, 276);

}

void Menu::OnMessage(MSG* msg)
{
	//char aaa[256];
	//_itoa_s(msg->message, aaa,2);
	//dv_font.DrawString(aaa, 10 , 210 ) ;   
	//PostQuitMessage(0);

	POINT mouse;
	mouse.x = LOWORD(msg->lParam);
	mouse.y = HIWORD(msg->lParam);

	switch (msg->message)
	{
	case WM_MOUSEMOVE:
		{
			for (int i = 0; i < 3; ++i)
			{
				if (PtInRect(&btn_box[i], mouse))
				{
					list_num = i;
					break;
				}
			}
			break;
		}

	case WM_LBUTTONDOWN:
		{
			if (PtInRect(&start_box, mouse))
			{
				g_Mng.n_Chap = GAME;
			}

			else if (PtInRect(&option_box, mouse))
			{
			}

			else if (PtInRect(&quit_box, mouse))
			{
				DestroyWindow(m_hWnd);
				return;
			}
		}
		break;
	}

}