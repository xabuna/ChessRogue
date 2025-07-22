#ifndef _BASICMATERIALEVALUATOR_H_
#define _BASICMATERIALEVALUATOR_H_

#include "IBoardEvaluator.h"   // IBoardEvaluator 상속을 위해 필수
#include "AIConfig.h"          // AIConfig::GetPieceValues() 사용을 위해 필수
#include "BoardController.h"   // Evaluator 함수 시그니처를 위해 BoardController 정의 필요 (만약 BoardController.h가 Include.h 안에 없다면)

// BoardController 클래스가 Include.h 안에 없다면, 여기에 BoardController.h를 명시적으로 포함해야 함.
// #include "BoardController.h"

// <algorithm>은 보통 구현 파일에서 사용되므로 여기서는 제거 가능
// #include <algorithm> 
class IBoardEvaluator;

class BasicMaterialEvaluator : public IBoardEvaluator {
public:
    BasicMaterialEvaluator();

    int Evaluator(BoardController& boardctrl);
};

#endif