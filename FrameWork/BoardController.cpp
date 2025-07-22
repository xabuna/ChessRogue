#include "BoardController.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

BoardController boardctrl; // ����..

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
// } �ּ� ó���ϴ� ���� �����ִ� �Ҹ���

BoardController::~BoardController() {
	for (Piece* p : ownedPieces) { // ownedPieces�� �ִ� ��� �����͸� ��ȸ�ϸ�
		delete p; // �޸� ����
	}
	ownedPieces.clear(); // ���� ����
}

//���� ¥���� ������ ������...
void BoardController::SetPiecesStarting()
{
	// AI �� ����
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		Pawn* newPawn = new Pawn(Pieceinfo{ AI_PAWN, i, AI, PIECE_PAWN });
		board[AI_PAWN][i] = newPawn;
		ownedPieces.push_back(newPawn); // ���Ϳ� �߰�
	}
	// �÷��̾� �� ����
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		Pawn* newPawn = new Pawn(Pieceinfo{ PLAYER_PAWN, i, PLAYER, PIECE_PAWN });
		board[PLAYER_PAWN][i] = newPawn;
		ownedPieces.push_back(newPawn); // ���Ϳ� �߰�
	}
	// AI �⹰ ����
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


	// �÷��̾� �⹰ ����
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
    undoInfo.move = move; // � ���� �״��� ���

    // ��� ��ġ�� �⹰ ��������
    Piece* pieceToMove = getPiece(move.fromRow, move.fromCol);

    // �������� �⹰�� �ִ��� Ȯ��
    Piece* capturedPiece = getPiece(move.toRow, move.toCol);

    // ���߿� �ǵ����� ���� ���� �⹰ ���� ���� 
    undoInfo.capturedPiece = capturedPiece;
    undoInfo.capturedPieceRow = move.toRow;
    undoInfo.capturedPieceCol = move.toCol;

    // �⹰ �̵� ����
    setPiece(move.toRow, move.toCol, pieceToMove); // �⹰�� �������� �̵�
    setPiece(move.fromRow, move.fromCol, nullptr); // ��� ��ġ�� ���

    // �⹰ ��ü�� ���� ��ġ ������ ������Ʈ
    if (pieceToMove != nullptr) {
        pieceToMove->setPosition(move.toRow, move.toCol);
    }

    // �̵� ���� ��ȯ / ���߿� �ǵ����� ����
    return undoInfo;
}

// �̵��� �ǵ����� �Լ�
void BoardController::UndoMoveForAI(const UndoInfo& undoInfo) {
    // �̵��ߴ� �⹰ ��������
    Piece* movedPiece = getPiece(undoInfo.move.toRow, undoInfo.move.toCol);

    // �⹰�� ���� ��ġ�� �ǵ���
    setPiece(undoInfo.move.fromRow, undoInfo.move.fromCol, movedPiece);

    // �⹰ ��ü�� ���� ��ġ ������ ������� �ǵ���
    if (movedPiece != nullptr) {
        movedPiece->setPosition(undoInfo.move.fromRow, undoInfo.move.fromCol);
    }

    // ������ �⹰�� �־��ٸ� �ٽ� ���� ��ġ�� ��ġ
    if (undoInfo.capturedPiece != nullptr) {
        setPiece(undoInfo.capturedPieceRow, undoInfo.capturedPieceCol, undoInfo.capturedPiece);
    }
    else {
        // ���� �⹰�� �����ٸ� �̵� �������� �����
        setPiece(undoInfo.move.toRow, undoInfo.move.toCol, nullptr);
    }
}