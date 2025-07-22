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

// BoardController::~BoardController()
// {
// 	for (int i=0; i< BOARD_SIZE; ++i)
// 		for (int j=0; j < BOARD_SIZE; ++j)
// 		{
// 			delete board[i][j];
// 			board[i][j] = nullptr;
// 		}
// } 주석 처리하는 원래 문제있던 소멸자

BoardController::~BoardController() {
	for (Piece* p : ownedPieces) { // ownedPieces에 있는 모든 포인터를 순회하며
		delete p; // 메모리 해제
	}
	ownedPieces.clear(); // 벡터 비우기
}

//벡터 짜놓은 것으로 수정중...
void BoardController::SetPiecesStarting()
{
	// AI 폰 생성
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		Pawn* newPawn = new Pawn(Pieceinfo{ AI_PAWN, i, AI, PIECE_PAWN });
		board[AI_PAWN][i] = newPawn;
		ownedPieces.push_back(newPawn); // 벡터에 추가
	}
	// 플레이어 폰 생성
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		Pawn* newPawn = new Pawn(Pieceinfo{ PLAYER_PAWN, i, PLAYER, PIECE_PAWN });
		board[PLAYER_PAWN][i] = newPawn;
		ownedPieces.push_back(newPawn); // 벡터에 추가
	}
	// AI 기물 생성
	Rook* newRookL_AI = new Rook(Pieceinfo{ AI_MINOR, ROOK_L, AI, PIECE_ROOK });
	board[AI_MINOR][ROOK_L] = newRookL_AI;
	ownedPieces.push_back(newRookL_AI);

	Knight* newKnightL_AI = new Knight(Pieceinfo{ AI_MINOR, KNIGHT_L, AI,PIECE_KNIGHT });
	board[AI_MINOR][KNIGHT_L] = newKnightL_AI;
	ownedPieces.push_back(newKnightL_AI);

	Bishop* newBishopL_AI = new Bishop(Pieceinfo{ AI_MINOR, BISHOP_L, AI, PIECE_BISHOP });
	board[AI_MINOR][BISHOP_L] = newBishopL_AI;
	ownedPieces.push_back(newBishopL_AI);

	Queen* newQueenBK_AI = new Queen(Pieceinfo{ AI_MINOR, QUEEN_BK, AI,PIECE_QUEEN });
	board[AI_MINOR][QUEEN_BK] = newQueenBK_AI;
	ownedPieces.push_back(newQueenBK_AI);

	King* newKingBK_AI = new King(Pieceinfo{ AI_MINOR, KING_BK, AI, PIECE_KING });
	board[AI_MINOR][KING_BK] = newKingBK_AI;
	ownedPieces.push_back(newKingBK_AI);

	Bishop* newBishopR_AI = new Bishop(Pieceinfo{ AI_MINOR, BISHOP_R, AI, PIECE_BISHOP });
	board[AI_MINOR][BISHOP_R] = newBishopR_AI;
	ownedPieces.push_back(newBishopR_AI);

	Knight* newKnightR_AI = new Knight(Pieceinfo{ AI_MINOR, KNIGHT_R, AI,PIECE_KNIGHT });
	board[AI_MINOR][KNIGHT_R] = newKnightR_AI;
	ownedPieces.push_back(newKnightR_AI);

	Rook* newRookR_AI = new Rook(Pieceinfo{ AI_MINOR, ROOK_R, AI, PIECE_ROOK });
	board[AI_MINOR][ROOK_R] = newRookR_AI;
	ownedPieces.push_back(newRookR_AI);


	// 플레이어 기물 생성
	Rook* newRookL_Player = new Rook(Pieceinfo{ PLAYER_MINOR, ROOK_L, PLAYER, PIECE_ROOK });
	board[PLAYER_MINOR][ROOK_L] = newRookL_Player;
	ownedPieces.push_back(newRookL_Player);

	Knight* newKnightL_Player = new Knight(Pieceinfo{ PLAYER_MINOR, KNIGHT_L, PLAYER,PIECE_KNIGHT });
	board[PLAYER_MINOR][KNIGHT_L] = newKnightL_Player;
	ownedPieces.push_back(newKnightL_Player);

	Bishop* newBishopL_Player = new Bishop(Pieceinfo{ PLAYER_MINOR, BISHOP_L, PLAYER, PIECE_BISHOP });
	board[PLAYER_MINOR][BISHOP_L] = newBishopL_Player;
	ownedPieces.push_back(newBishopL_Player);

	King* newKingWH_Player = new King(Pieceinfo{ PLAYER_MINOR, KING_WH , PLAYER, PIECE_KING });
	board[PLAYER_MINOR][KING_WH] = newKingWH_Player;
	ownedPieces.push_back(newKingWH_Player);

	Queen* newQueenWH_Player = new Queen(Pieceinfo{ PLAYER_MINOR, QUEEN_WH, PLAYER,PIECE_QUEEN });
	board[PLAYER_MINOR][QUEEN_WH] = newQueenWH_Player;
	ownedPieces.push_back(newQueenWH_Player);

	Bishop* newBishopR_Player = new Bishop(Pieceinfo{ PLAYER_MINOR, BISHOP_R, PLAYER, PIECE_BISHOP });
	board[PLAYER_MINOR][BISHOP_R] = newBishopR_Player;
	ownedPieces.push_back(newBishopR_Player);

	Knight* newKnightR_Player = new Knight(Pieceinfo{ PLAYER_MINOR, KNIGHT_R, PLAYER,PIECE_KNIGHT });
	board[PLAYER_MINOR][KNIGHT_R] = newKnightR_Player;
	ownedPieces.push_back(newKnightR_Player);

	Rook* newRookR_Player = new Rook(Pieceinfo{ PLAYER_MINOR, ROOK_R, PLAYER, PIECE_ROOK });
	board[PLAYER_MINOR][ROOK_R] = newRookR_Player;
	ownedPieces.push_back(newRookR_Player);
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


BoardController::UndoInfo BoardController::ApplyMoveForAI(const MoveLogic::Move& move) {
    UndoInfo undoInfo;
    undoInfo.move = move; // 어떤 수를 뒀는지 기록

    // 출발 위치의 기물 가져오기
    Piece* pieceToMove = getPiece(move.fromRow, move.fromCol);

    // 목적지에 기물이 있는지 확인
    Piece* capturedPiece = getPiece(move.toRow, move.toCol);

    // 나중에 되돌리기 위해 잡힌 기물 정보 저장 
    undoInfo.capturedPiece = capturedPiece;
    undoInfo.capturedPieceRow = move.toRow;
    undoInfo.capturedPieceCol = move.toCol;

    // 기물 이동 실행
    setPiece(move.toRow, move.toCol, pieceToMove); // 기물을 목적지로 이동
    setPiece(move.fromRow, move.fromCol, nullptr); // 출발 위치는 비움

    // 기물 객체의 내부 위치 정보도 업데이트
    if (pieceToMove != nullptr) {
        pieceToMove->setPosition(move.toRow, move.toCol);
    }

    // 이동 정보 반환 / 나중에 되돌리기 위해
    return undoInfo;
}

// 이동을 되돌리는 함수
void BoardController::UndoMoveForAI(const UndoInfo& undoInfo) {
    // 이동했던 기물 가져오기
    Piece* movedPiece = getPiece(undoInfo.move.toRow, undoInfo.move.toCol);

    // 기물을 원래 위치로 되돌림
    setPiece(undoInfo.move.fromRow, undoInfo.move.fromCol, movedPiece);

    // 기물 객체의 내부 위치 정보도 원래대로 되돌림
    if (movedPiece != nullptr) {
        movedPiece->setPosition(undoInfo.move.fromRow, undoInfo.move.fromCol);
    }

    // 잡혔던 기물이 있었다면 다시 원래 위치에 배치
    if (undoInfo.capturedPiece != nullptr) {
        setPiece(undoInfo.capturedPieceRow, undoInfo.capturedPieceCol, undoInfo.capturedPiece);
    }
    else {
        // 잡힌 기물이 없었다면 이동 목적지는 비워둠
        setPiece(undoInfo.move.toRow, undoInfo.move.toCol, nullptr);
    }
}