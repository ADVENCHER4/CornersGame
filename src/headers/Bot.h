#pragma once
#include "Field.h"
#include "Constants.h"
#include <math.h>
#include <limits>
struct MoveVariant                     // вариант хода бота
{
   Checker* _checker;                  // какой шашкой ходит
   Move _move;                         // куда
   MoveVariant(): _checker(nullptr) {}
};

class Bot
{
private:
   double evaluation(Field*);          // оценочная ф-ция
   double miniMax(Field*, int, bool);  // минимакс
   double alphaBeta(Field*, int, bool, double, double);// альфа-бета
public:
   Bot();
   MoveVariant chooseMove(Field*);     // ф-ция выбора хода
};