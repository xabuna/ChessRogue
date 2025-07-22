#ifndef _IBoardEvaluator_H_
#define _IBoardEvaluator_H_
// BoardController Ŭ������ �ʿ��ϹǷ� ���� ����
#include "BoardController.h"

/**
 * ü�� ���� �� �������̽�
 * ��� �� �Լ� ������ �� Ŭ������ ��ӹ޾ƾ� ��
 * �� ����ü�� ���� ���¸� ���Ͽ� ������ ��ȯ�ؾ� ��
 */
class IBoardEvaluator {
public:
	// ���� �Ҹ���
	virtual ~IBoardEvaluator() = default;

	// ���� ���¸� ���Ͽ� ������ ��ȯ�ϴ� ���� ���� �Լ�
	// ���: AI ����, ����: �÷��̾� ����
	virtual int Evaluator(BoardController& boardctrl) = 0;
};
#endif