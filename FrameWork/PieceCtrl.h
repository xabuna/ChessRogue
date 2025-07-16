#ifndef _PIECECTRL_H_
#define _PIECECTRL_H_

#include "Include.h"
//#include <vector>
class Piece;
class BoardController;

class PieceCtrl {

    Sprite Highlight;
    Sprite GhostPiece;

    int Turn = PLAYER;

	/////////////////////////////////////
	bool pieceSelected = false; // 기물 선택
	int selectedRow = -1; // 선택한 기물 행
	int selectedCol = -1; // 선택한 기물 열
	/////////////////////////////////////

public:


    Piece* selectedPiece;
    BoardController* boardRef = nullptr;
   
    void HighlightInit();
    void HighlightDraw(int _col, int _row);
    void HighlightUpdate();
    void HighlightFollow();
    void HighlightClear();

    void GhostPieceInit();
    void GhostPieceDraw();
    void GhostPieceUpdate();

    bool Move(int fromRow, int fromCol, int toRow, int toCol);
    
    void UpdatePos(Piece* piece, int toRow, int toCol);
    
    void Remove(int row, int col);
    
    bool Promotable(Piece* piece);

    void PieceMove(int mouseX, int mouseY); // key.cpp에서 좌클릭 호출

    void SwitchTurn();

    POINT HandleMouseClick(int mouseY, int mouseX);
	// /////////////////////////////////////
	// bool pieceSelected = false; // 기물 선택
	// int selectedRow = -1; // 선택한 기물 행
	// int selectedCol = -1; // 선택한 기물 열
	// /////////////////////////////////////
};

extern PieceCtrl pieceCtrl;
#endif