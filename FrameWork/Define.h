#define SCREEN_WITH 1680	// ȭ�� ���� �ȼ�ũ��
#define SCREEN_HEIGHT 1050	// ȭ�� ���� �ȼ�ũ��

#define FRAME 1000
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define ON 1
#define OFF 0

//�⹰�� ����
#define ALIVE 1
#define DEAD 0

//�������� �ִ� �⹰�� ������ ���ΰ�
#define EMPTY 0
#define AI 1
#define PLAYER 2

//�⹰�� ����
#define BLACK 0
#define WHITE 1
/*===========================================================*/
#define TILE 110
#define BOARDSTART_X 400
#define BOARDSTART_Y 80
#define BOARD_SIZE 8

#define ITEMTILE 115
#define ITEMSTART_X 90
#define ITEMSTART_Y 255
#define ITME_SPACE 15
/*===========================================================*/
///////////////////////////////////////////////////////////////
//////////////////// PIECE �迭�� ���/////////////////////////

enum { AI_MINOR = 0, AI_PAWN = 1, PLAYER_PAWN = 6, PLAYER_MINOR = 7 }; // �� ��ġ PLAYER�� �ؿ��� 1ĭ ����, AI�� ������ 1ĭ �Ʒ� 
enum { ROOK_L = 0, KNIGHT_L = 1, BISHOP_L = 2, BISHOP_R = 5, KNIGHT_R = 6, ROOK_R = 7 }; // ���̳��ǽ� ��ġ
enum { QUEEN_WH = 3, QUEEN_BK = 3 };
enum { KING_BK = 4, KING_WH = 4 };

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/*===========================================================*/
///////////////////////////////////////////////////////////////
///////////////////////PIECETYPE MAP///////////////////////////
enum PieceType {
	PIECE_NONE = 0,
	PIECE_PAWN = 1,
	PIECE_BISHOP = 2,
	PIECE_KNIGHT = 3,
	PIECE_ROOK = 4,
	PIECE_QUEEN = 5,
	PIECE_KING = 6
};
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/*===========================================================*/
///////////////////////////////////////////////////////////////
//////////////////////////	������	///////////////////////////

#define PAWN_T		10000000
#define BISHOP_T	20000000
#define KNIGHT_T	30000000
#define ROOK_T		40000000
#define QUEEN_T		50000000
#define KING_T		60000000
#define ENEMY_T     70000000
#define PIECES_T    80000000

#define NORMAL		 1000000
#define RARE		 2000000
#define ELITE		 3000000
#define EPIC		 4000000
#define LEGEND		 5000000
#define FABLE		 6000000

#define ATKITEM		   10000
#define DEFITEM		   20000
#define PROMITEM	   30000
#define HEALITEM	   40000
#define ACTITEM
#define BUFFITEM	   60000
#define DBUFFITEM	   70000

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/*=======================��Ʋ������==========================*/
#define CRITICAL_HIT_CHANCE 20  // 20% Ȯ��
#define CRITICAL_HIT_MULTIPLIER 2

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/*===========================================================*/
// ����Ÿ ���̽�
#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "2708"
#define DB_NAME "test"
#define CHOP(x) x[strlen(x) - 1] = ' ' // �����ٰ� �Ⱦ�...

enum gamechap
{
	LOGO = 0,
	MENU = 1,
	GAME = 2,
	OVER = 3,
	TOTALCHAP
};

enum alphabet
{
	A_, B_, C_, D_, E_, F_, G_, H_, I_, J_, K_, L_
};
enum gamework
{
	INIT = 0,
	WORK = 1,
	DRAW = 2
};