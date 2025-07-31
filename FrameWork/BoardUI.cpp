#include "BoardUI.h"

BoardUI boardUI;

BoardUI::BoardUI()
{
	/*for (int i = 0; i < 4; ++i)
	{
	Inventory[i][0] = nullptr;
	}*/
}

BoardUI::~BoardUI()
{
	/*for (int i = 0; i < 4; ++i)
	{
		delete Inventory[i][0];
		Inventory[i][0] = nullptr;
	}*/
}

void BoardUI::InvenInit() {

	char FileName[256];

	sprintf_s(FileName, "./resource/Img/chess/UI/inventory.png");
	Inventory_img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	/*for (int i = 0; i < 4; ++i)
	{
		Inventory[i][0] = nullptr;
	}*/
}
void BoardUI::InvenDraw() {
	if (Gmanager.m_GameStart == true)
	{
		Inventory_img.SetColor(255, 255, 255, 255);
		Inventory_img.Draw(60+background.posX,80);

		/*for (int i = 0; i < 4; ++i)
		{
			if(Inventory[i][0] != nullptr);
			Inventory->Draw();
		}*/
	}
}
void BoardUI::InvenUpdate() {

}

void BoardUI::BattlelogInit() {

	char FileName[256];

	sprintf_s(FileName, "./resource/Img/chess/UI/battlelog.png");
	Battlelog_img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}
void BoardUI::BattlelogDraw() {

	Battlelog_img.SetColor(255, 255, 255, 255);
	//처음 그려지는 위치
	Battlelog_img.Draw(1345 + background.posX, 80);	//IMAGE[Index].Render(x 좌표,y 좌표,방향변수(이미지의 회전),x 사이즈,y사이즈,중심점);
}

void BoardUI::BattlelogUpdate() {

}