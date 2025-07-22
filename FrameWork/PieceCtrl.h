#ifndef _PIECECTRL_H_
#define _PIECECTRL_H_

#include "Move.h"
#include "Include.h"

class Piece;
class BoardController;

class PieceCtrl {

    Sprite Highlight;
    Sprite GhostPiece;

    DWORD aiTurnStartTime = 0;
    bool aiWaiting = false;

    int Turn = PLAYER;

	/////////////////////////////////////
	bool pieceSelected = false; // 기물 선택
	int selectedRow = -1; // 선택한 기물 행
	int selectedCol = -1; // 선택한 기물 열 
    int currentRow = -1;
    int currentCol = -1;
	/////////////////////////////////////

public:



    void UpdateAITurnDelay();

    Piece* selectedPiece;
    BoardController* boardRef = nullptr;
   
    void HighlightInit();
    void HighlightDraw(int _col, int _row);
    void HighlightUpdate();
    void HighlightFollow(int currentX, int currentY);
    void HighlightClear();

    void GhostPieceInit();
    void GhostPieceDraw();
    void GhostPieceUpdate();

    bool Move(int fromRow, int fromCol, int toRow, int toCol);

    bool Move(const MoveLogic::Move& move); // 오버로드

    void UpdatePos(Piece* piece, int toRow, int toCol);
    
    void Remove(int row, int col);
    
    bool Promotable(Piece* piece);

    void PieceMove(int mouseX, int mouseY); // key.cpp에서 좌클릭 호출

    void SwitchTurn();

    POINT HandleMouseClick(int mouseY, int mouseX);

    int GetTurn() const { return Turn; }

	void ProcessAITurn();
	void ForceAIMove(); // 테스트용 강제 진행

};

extern PieceCtrl pieceCtrl;
#endif