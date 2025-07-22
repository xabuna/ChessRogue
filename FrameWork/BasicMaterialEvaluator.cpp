#include "BasicMaterialEvaluator.h"

// �� �Լ� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BasicMaterialEvaluator::BasicMaterialEvaluator() {} 

int BasicMaterialEvaluator::Evaluator(BoardController& boardctrl) {

	// ��ȸ ���̺�� ����� map �������
	const std::map<PieceType, int>& pieceValuesMap = AIConfig::GetPieceValues();
	// ���� ���� ������ ���� 0���� �ʱ�ȭ
	int score = 0;

	//�⹰ �������
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			Piece* currentPiece = boardctrl.getPiece(row, col);

			if (currentPiece != nullptr && currentPiece->getAlive()) {
				// �⹰�� type�� owner ������ ������
				PieceType pieceType = currentPiece->getType();
				int owner = currentPiece->getOwner(); // Piece Ŭ������ getOwner()�� ������

				auto it = pieceValuesMap.find(pieceType); 
				int pieceValues = 0;

				if (it != pieceValuesMap.end())
					pieceValues = it->second;

				// AI(�ڽ�)�� �⹰�� + ����
				if (AI == currentPiece->getOwner())
					score += pieceValues;

				// �÷��̾��� �⹰�� - ����
				else if (PLAYER == currentPiece->getOwner())
					score -= pieceValues;
			}
		}
	}
	// 2. �⵿�� (Mobility) ��
// AI �⹰���� �̵��� �� �ִ� ĭ�� ���� ������ �ο�.
// �� �⹰�� �󸶳� �����Ӱ� ������ �� �ִ��� ����.
// �̵� ���� ���� ������ +����, ������ -���� (���� ���, ������ �� ����)
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
	score += (aiMobilityScore - playerMobilityScore) * 10; // ������ ����ġ (��: 10��)

	// 3. �߾� ��Ƿ� (Center Control) ��
	// ü�� ���� �߾� 4ĭ(d4, d5, e4, e5)�� �⹰�̳� ���� ���� �� ���� �ο�.
	// �߾� 4ĭ: (3,3), (3,4), (4,3), (4,4)
	// �� ���� �߾� ������ ����� ���� ����.
	int centerControlScore = 0;
	int centerSquares[4][2] = { {3,3}, {3,4}, {4,3}, {4,4} }; // (row, col)
	for (int i = 0; i < 4; ++i) {
		int r = centerSquares[i][0];
		int c = centerSquares[i][1];
		Piece* p = boardctrl.getPiece(r, c);
		if (p != nullptr && p->getAlive()) {
			if (p->getOwner() == AI) centerControlScore += 30; // AI �⹰�� �߾ӿ� ������ +30
			else if (p->getOwner() == PLAYER) centerControlScore -= 30; // ��� �⹰�� �߾ӿ� ������ -30
		}
	}
	score += centerControlScore;


	// 4. �� ���� (Pawn Structure) �� (�� ���)
	// - �� �� ��(Doubled Pawns): ���� ���� ���� 2�� �̻� ������ -����
	// - �� ��(Isolated Pawns): �� ���� �Ʊ� ���� ������ -����
	// - ���� ��(Passed Pawns): ��� ������ ������ �ʰ� ������ �� �ִ� ���� ������ +����
	// �� �κ��� ���� ��ġ�� Ȯ���ϴ� ������ ������ �ʿ���.


	// 5. ŷ ������ (King Safety) �� (�� ���)
	// - ŷ �ֺ��� �� ���� �󸶳� ưư���� (+����)
	// - ŷ �ֺ��� �� �⹰�� �����ϴ��� (-����)
	// �� �κ��� ŷ�� ��ġ�� �ֺ� ĭ���� Ȯ���ϴ� ������ �ʿ���.


	// 6. �⹰ ���� (Development) �� Ȱ���� (Activity) �� (�� ���)
	// - ĳ���� ���� (+����)
	// - �⹰���� �ʱ� ��ġ���� ��� �߾ӿ� ������ ��ġ�ߴ��� (+����)
	// - ����Ʈ�� ���� �߾ӿ� ������ +����, �����ڸ��� ������ -����


	return score;
}