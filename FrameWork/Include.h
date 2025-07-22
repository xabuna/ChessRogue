#pragma once

/* ---------------------------------------------------
///////////////// ���α׷� ���� //////////////////////

		���̺귯���� �ʿ��� �����Դϴ�.
		����� �ȵſ�~~^^;

//////////////////////////////////////////////////////
-----------------------------------------------------*/

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dsound.lib")

// ����Ÿ ���̽�///////////////////
//#include <my_global.h>
#include <winsock2.h>
#include <mysql.h>
#pragma comment(lib, "libmySQL.lib")

//////////////////////////////////

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <dsound.h>
//#include "DXUTsound.h"
#include <list>

#include "Define.h"
#include "DeviceFont.h"
#include "Sprite.h"
#include "Chap.h"


/* ---------------------------------------------------
///////////////// ����� �߰� ���� ///////////////////

		���� Ŭ���� ���� �� ����
		��������� �߰��� �ּ���~

//////////////////////////////////////////////////////
-----------------------------------------------------*/
#include <vector>
#include <utility>

#include "Game.h"
#include "Logo.h"
#include "Menu.h"
#include "Over.h"
#include "CMng.h"

//#include "Night.h"

#include "Camera.h"

#include "Map.h"

#include "Key.h"
//#include "Sound.h"
#include "FMOD.h"
///////////////////////////////////////////////////////
#include "Move.h"
#include "Piece.h"

#include "Board.h"
#include "BoardUI.h"
#include "Transition.h"
#include "TransitionChar.h"
#include "BoardController.h"

#include "IBoardEvaluator.h"
#include "BasicMaterialEvaluator.h"
#include "ChessAI.h"
///////////////////////////////////////////////////////4
#include "PieceCtrl.h"
#include "BattleAnimation.h"
///////////////////////////////////////////////////////

#include "BattleManager.h"
///////////////////////////////////////////////////////
#include "Player.h"
#include "Player2.h"
#include "Collider.h"

#include "GameManager.h"
// ����Ÿ ���̽�///////////////////
#include "Mysql.h"

/* ---------------------------------------------------
///////////////// ����� �߰� ���� ///////////////////

		Ű �Է� ó�� �Լ��Դϴ�.

//////////////////////////////////////////////////////
-----------------------------------------------------*/

inline int KeyDown	( int vk ) 
{ 
	return ( (GetAsyncKeyState(vk) & 0x8000) ? 1:0 ); 
}

inline int KeyUp	( int vk ) 
{ 
	return ( (GetAsyncKeyState(vk) & 0x8000) ? 0:1 ); 
}