#ifndef _BOARDUI_H_
#define _BOARDUI_H_

#include "include.h"

//class Item;

class BoardUI 
{
	//Item* Inventory[4][1];

private:
	Sprite Inventory_img;
	Sprite Battlelog_img;
	//Item *Inventory [4][1];
public:
	BoardUI();
	~BoardUI();

	void InvenInit();
	void InvenDraw();
	void InvenUpdate();

	void BattlelogInit();
	void BattlelogDraw();
	void BattlelogUpdate();
};

extern BoardUI boardUI;

#endif