#include "BasicMaterialEvaluator.h"
#include "Piece.h" 

// 평가 함수 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BasicMaterialEvaluator::BasicMaterialEvaluator() {} 

int BasicMaterialEvaluator::Evaluator(BoardController& boardctrl) {

	// 조회 테이블로 사용할 map 갖고오기
	const std::map<PieceType, int>& pieceValuesMap = AIConfig::GetPieceValues();
	// 최종 점수 저장할 변수 0으로 초기화
	int score = 0;

    // AI와 플레이어의 킹 위치를 저장할 변수/ 루프 돌면서 업데이트함.
    int aiKingRow = -1, aiKingCol = -1;
    int playerKingRow = -1, playerKingCol = -1;

    //==================================================================================
    // 1. 기물 가치 평가 (Material Value)		 HP 반영
    //==================================================================================
    // 설명: 각 기물의 기본 점수에 현재 HP 비율을 곱하여 동적인 가치를 산정합니다.
    //       HP가 낮은 기물은 가치가 낮아지므로, AI가 해당 기물을 무리하게 사용하지 않거나
    //       반대로 상대의 HP 낮은 기물을 우선적으로 노리게 만드는 핵심 로직입니다.
    //----------------------------------------------------------------------------------
	//기물 갖고오기
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			Piece* currentPiece = boardctrl.getPiece(row, col);

            // 해당 칸에 기물이 존재하고, 살아있는 상태인지 확인
			if (currentPiece != nullptr && currentPiece->getAlive()) {
				// 기물의 type과 owner 정보를 가져옴
				PieceType pieceType = currentPiece->getType();
				int owner = currentPiece->getOwner(); // Piece 클래스의 getOwner()로 가져옴

                // 일단 킹의 위치를 찾음
                if (pieceType == PIECE_KING) {
                    if (owner == AI) {
                        aiKingRow = row;
                        aiKingCol = col;
                    }
                    else {
                        playerKingRow = row;
                        playerKingCol = col;
                    }
                }

				auto it = pieceValuesMap.find(pieceType); 
				int pieceValues = 0;

				if (it != pieceValuesMap.end())
					pieceValues = it->second;

				// AI(자신)의 기물은 + 점수
				if (AI == currentPiece->getOwner())
					score += pieceValues;

				// 플레이어의 기물은 - 점수
				else if (PLAYER == currentPiece->getOwner())
					score -= pieceValues;
			}
		}
	}
	// 2. 기동성 (Mobility) 평가
// AI 기물들이 이동할 수 있는 칸의 수에 점수를 부여.
// 각 기물이 얼마나 자유롭게 움직일 수 있는지 측정.
// 이동 가능 수가 많으면 +점수, 적으면 -점수 (수동 계산, 복잡할 수 있음)
	int aiMobilityScore = 0;
	int playerMobilityScore = 0;
	for (int r = 0; r < BOARD_SIZE; ++r) {
		for (int c = 0; c < BOARD_SIZE; ++c) {
			Piece* p = boardctrl.getPiece(r, c);
			if (p != nullptr && p->getAlive()) {
				std::vector<std::pair<int, int>> moves = p->getLegalMoves(&boardctrl);
				if (p->getOwner() == AI) {
					aiMobilityScore += moves.size();
				}
				else if (p->getOwner() == PLAYER) {
					playerMobilityScore += moves.size();
				}
			}
		}
	}
	score += (aiMobilityScore - playerMobilityScore) * 10; // 적절한 가중치 (예: 10점)

	// 3. 중앙 장악력 (Center Control) 평가
	// 체스 보드 중앙 4칸(d4, d5, e4, e5)에 기물이나 폰이 있을 때 점수 부여.
	// 중앙 4칸: (3,3), (3,4), (4,3), (4,4)
	// 더 넓은 중앙 영역을 고려할 수도 있음.
	int centerControlScore = 0;
	int centerSquares[4][2] = { {3,3}, {3,4}, {4,3}, {4,4} }; // (row, col)
	for (int i = 0; i < 4; ++i) {
		int r = centerSquares[i][0];
		int c = centerSquares[i][1];
		Piece* p = boardctrl.getPiece(r, c);
		if (p != nullptr && p->getAlive()) {
			if (p->getOwner() == AI) centerControlScore += 30; // AI 기물이 중앙에 있으면 +30
			else if (p->getOwner() == PLAYER) centerControlScore -= 30; // 상대 기물이 중앙에 있으면 -30
		}
	}
	score += centerControlScore;


	// 4. 폰 구조 (Pawn Structure) 평가 (더 고급)
	// - 두 배 폰(Doubled Pawns): 같은 열에 폰이 2개 이상 있으면 -점수
	// - 고립 폰(Isolated Pawns): 옆 열에 아군 폰이 없으면 -점수
	// - 전진 폰(Passed Pawns): 상대 폰에게 막히지 않고 승진할 수 있는 폰이 있으면 +점수
	// 이 부분은 폰의 위치를 확인하는 복잡한 로직이 필요함.


	// 5. 킹 안정성 (King Safety) 평가 (더 고급)
	// - 킹 주변의 폰 벽이 얼마나 튼튼한지 (+점수)
	// - 킹 주변에 적 기물이 위협하는지 (-점수)
	// 이 부분은 킹의 위치와 주변 칸들을 확인하는 로직이 필요함.


	// 6. 기물 전개 (Development) 및 활동성 (Activity) 평가 (더 고급)
	// - 캐슬링 여부 (+점수)
	// - 기물들이 초기 위치에서 벗어나 중앙에 가까이 위치했는지 (+점수)
	// - 나이트가 보드 중앙에 있으면 +점수, 가장자리에 있으면 -점수


	return score;
}