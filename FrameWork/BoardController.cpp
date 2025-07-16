#include "BoardController.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

BoardController boardctrl; // 전역..

//enum { AI = 1, PLAYER = 2 };


BoardController::BoardController() 
{
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			board[i][j] = nullptr;
		}
}

BoardController::~BoardController()
{
	for (int i=0; i< BOARD_SIZE; ++i)
		for (int j=0; j < BOARD_SIZE; ++j)
		{
			delete board[i][j];
			board[i][j] = nullptr;
		}
}

//벡터 짜놓은 것으로 수정중...
void BoardController::SetPiecesStarting()
{
	// AI 폰 생성
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		board[AI_PAWN][i] = new Pawn(Pieceinfo{ AI_PAWN, i, AI });
	}
	// 플레이어 폰 생성
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		board[PLAYER_PAWN][i] = new Pawn(Pieceinfo{ PLAYER_PAWN, i, PLAYER });
	}
	// AI 기물 생성
	board[AI_MINOR][ROOK_L] = new Rook(Pieceinfo{ AI_MINOR, ROOK_L, AI });
	board[AI_MINOR][KNIGHT_L] = new Knight(Pieceinfo{ AI_MINOR, KNIGHT_L, AI });
	board[AI_MINOR][BISHOP_L] = new Bishop(Pieceinfo{ AI_MINOR, BISHOP_L, AI });
	board[AI_MINOR][QUEEN_BK] = new Queen(Pieceinfo{ AI_MINOR, QUEEN_BK, AI });
	board[AI_MINOR][KING_BK] = new King(Pieceinfo{ AI_MINOR, KING_BK, AI });
	board[AI_MINOR][BISHOP_R] = new Bishop(Pieceinfo{ AI_MINOR, BISHOP_R, AI });
	board[AI_MINOR][KNIGHT_R] = new Knight(Pieceinfo{ AI_MINOR, KNIGHT_R, AI });
	board[AI_MINOR][ROOK_R] = new Rook(Pieceinfo{ AI_MINOR, ROOK_R, AI });

	// 플레이어 기물 생성

	board[PLAYER_MINOR][ROOK_L] = new Rook(Pieceinfo{ PLAYER_MINOR, ROOK_L, PLAYER });
	board[PLAYER_MINOR][KNIGHT_L] = new Knight(Pieceinfo{ PLAYER_MINOR, KNIGHT_L, PLAYER });
	board[PLAYER_MINOR][BISHOP_L] = new Bishop(Pieceinfo{ PLAYER_MINOR, BISHOP_L, PLAYER });
	board[PLAYER_MINOR][KING_WH] = new King(Pieceinfo{ PLAYER_MINOR, KING_WH , PLAYER });
	board[PLAYER_MINOR][QUEEN_WH] = new Queen(Pieceinfo{ PLAYER_MINOR, QUEEN_WH, PLAYER });
	board[PLAYER_MINOR][BISHOP_R] = new Bishop(Pieceinfo{ PLAYER_MINOR, BISHOP_R, PLAYER });
	board[PLAYER_MINOR][KNIGHT_R] = new Knight(Pieceinfo{ PLAYER_MINOR, KNIGHT_R, PLAYER });
	board[PLAYER_MINOR][ROOK_R] = new Rook(Pieceinfo{ PLAYER_MINOR, ROOK_R, PLAYER });
}


void BoardController::Init()
{
	SetPiecesStarting();
}

void BoardController::Draw()
{
	for (int row = 0; row < BOARD_SIZE; ++row)
	{
		for (int col = 0; col < BOARD_SIZE; ++col)
		{
			if (board[row][col] != nullptr)
				board[row][col]->Draw();
		}
	}
}

Piece* BoardController::getPiece(int row, int col) const {

	if (col >= 0 && col < BOARD_SIZE && row >= 0 && row < BOARD_SIZE)
	{
		return board[row][col];
	}

	return nullptr;

}

void BoardController::setPiece(int row, int col, Piece* piece)
{
	if (col >= 0 && col < BOARD_SIZE && row >= 0 && row < BOARD_SIZE)
	{
		board[row][col] = piece;
	}
}
//void BoardController::RemovePiece(int row, int col){
//}