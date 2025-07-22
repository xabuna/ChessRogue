#pragma once

#include <map>
#include "Piece.h" // PieceType이 정의된 헤더 파일

class AIConfig {
public:
    static const std::map<PieceType, int>& GetPieceValues() {
        static const std::map<PieceType, int> pieceValues = {
            {PIECE_PAWN, 100},
            {PIECE_KNIGHT, 300},
            {PIECE_BISHOP, 300},
            {PIECE_ROOK, 500},
            {PIECE_QUEEN, 900},
            {PIECE_KING, 58778285}
        };
        return pieceValues;
    }
};