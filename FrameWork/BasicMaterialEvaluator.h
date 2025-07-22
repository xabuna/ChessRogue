#ifndef _BASICMATERIALEVALUATOR_H_
#define _BASICMATERIALEVALUATOR_H_

#include "IBoardEvaluator.h"   // IBoardEvaluator ����� ���� �ʼ�
#include "AIConfig.h"          // AIConfig::GetPieceValues() ����� ���� �ʼ�
#include "BoardController.h"   // Evaluator �Լ� �ñ״�ó�� ���� BoardController ���� �ʿ� (���� BoardController.h�� Include.h �ȿ� ���ٸ�)

// BoardController Ŭ������ Include.h �ȿ� ���ٸ�, ���⿡ BoardController.h�� ��������� �����ؾ� ��.
// #include "BoardController.h"

// <algorithm>�� ���� ���� ���Ͽ��� ���ǹǷ� ���⼭�� ���� ����
// #include <algorithm> 
class IBoardEvaluator;

class BasicMaterialEvaluator : public IBoardEvaluator {
public:
    BasicMaterialEvaluator();

    int Evaluator(BoardController& boardctrl);
};

#endif