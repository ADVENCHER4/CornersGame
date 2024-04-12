#pragma once
#include "Field.h"
#include "Constants.h"
#include <math.h>
#include <limits>
struct MoveVariant                     // ������� ���� ����
{
   Checker* _checker;                  // ����� ������ �����
   Move _move;                         // ����
   MoveVariant(): _checker(nullptr) {}
};

class Bot
{
private:
   double evaluation(Field*);          // ��������� �-���
   double miniMax(Field*, int, bool);  // ��������
   double alphaBeta(Field*, int, bool, double, double);// �����-����
public:
   Bot();
   MoveVariant chooseMove(Field*);     // �-��� ������ ����
};