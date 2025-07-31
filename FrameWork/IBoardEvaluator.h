#ifndef _IBoardEvaluator_H_
#define _IBoardEvaluator_H_
// BoardController 클래스만 필요하므로 직접 포함
#include "BoardController.h"

/**
 * 체스 보드 평가 인터페이스
 * 모든 평가 함수 구현은 이 클래스를 상속받아야 함
 * 각 구현체는 보드 상태를 평가하여 점수를 반환해야 함
 */
class IBoardEvaluator {
public:
	// 가상 소멸자
	virtual ~IBoardEvaluator() = default;

	// 보드 상태를 평가하여 점수를 반환하는 순수 가상 함수
	// 양수: AI 유리, 음수: 플레이어 유리
	virtual int Evaluator(BoardController& boardctrl) = 0;
};
#endif