#ifndef _BASICMATERIALEVALUATOR_H_
#define _BASICMATERIALEVALUATOR_H_

#include "IBoardEvaluator.h"   // IBoardEvaluator 상속을 위해 필수
#include "AIConfig.h"          // AIConfig::GetPieceValues() 사용을 위해 필수
#include "BoardController.h"   // Evaluator 함수 시그니처를 위해 BoardController 정의 필요 (만약 BoardController.h가 Include.h 안에 없다면)

class IBoardEvaluator;

class BasicMaterialEvaluator : public IBoardEvaluator {
public:
    BasicMaterialEvaluator();

    int Evaluator(BoardController& boardctrl);

};

#endif