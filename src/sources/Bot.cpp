#include "../headers/Bot.h"
#include <iostream>

Bot::Bot() = default;

MoveVariant Bot::chooseMove(Field* field)
{
   double maxEval = -std::numeric_limits<double>::infinity();        // ��������� ���� ����
   double alpha = -std::numeric_limits<double>::infinity();
   double beta = std::numeric_limits<double>::infinity();
   MoveVariant bestMove;
   Checker** checkers = field->getCheckers(BLACK);
   for (int i = 0; i < CHECKERS_COUNT; i++)                          // ���������, ���� �� �����, ������� ��� ������
   {
      Checker* checker = checkers[i];
      if (checker->getJumped())                                      // ���� ����� ������
      {
         List<Move> moves;
         field->generateMoves(checker, moves);
         for (int j = 0; j < moves.getLength(); j++)                 // ������������� ��� ���� ��� ��
         {
            Move move = moves.get(j);
            Field* editedField = field->copy();                      // �������� ������� ������� �� ����
            editedField->moveChecker(editedField->getCheckers(BLACK)[i], move.x, move.y);    // ��������� ���
            double eval = alphaBeta(editedField, DEPTH, false, alpha, beta);        // ��������� ���
            if (eval > maxEval)                                      // ���� �� ����� �����������
            {
               maxEval = eval;                                       // ���������� ���
               bestMove._checker = checker;
               bestMove._move = move;
            }
            if (eval > alpha)                                        // ����� ���� ���������
            {
               alpha = eval;
            }
            if (beta <= alpha)
               break;
            delete editedField;
         }
         return bestMove;
      }
   }
   for (int i = 0; i < CHECKERS_COUNT; i++)                          // ������������� ��� �����
   {
      List<Move> moves;
      Checker* checker = checkers[i];
      field->generateMoves(checker, moves);
      for (int j = 0; j < moves.getLength(); j++)                    // ������������� ��� ���� ��� ������� �����
      {
         Move move = moves.get(j);
         Field* editedField = field->copy();                         // �������� ����
         editedField->moveChecker(editedField->getCheckers(BLACK)[i], move.x, move.y);    // ��������� ���
         double eval = alphaBeta(editedField, DEPTH, false, alpha, beta);           // ��������� ������� ����� ���������� ����
         if (eval > maxEval)                                         // ���� �� �����, ���������� ���
         {
            maxEval = eval;
            bestMove._checker = checker;
            bestMove._move = move;
         }
         if (eval > alpha)                                           // �����-���� ���������
         {
            alpha = eval;
         }
         if (beta <= alpha)
            break;
         delete editedField;
      }
   }
   return bestMove;
}

double Bot::evaluation(Field* field)
{
   double blackScore = 0;
   double whiteScore = 0;
   double multiplier = 0;
   double maxDistance = sqrt(2 * FIELD_SIZE * FIELD_SIZE);
   double whiteExp = 1;
   double blackExp = 1;
   // � ������ �������� �������, � ��������� ���� ����� �������, ��� � ������, �� ��������, ��� � ����� ����
   for (int y = 0; y < FIELD_SIZE; y++)
   {
      for (int x = 0; x < FIELD_SIZE; x++)
      {
         Checker* checker = field->getChecker(x, y);
         if (!checker)
            continue;
         if (checker->getColor() == WHITE)
         {
            if (x < 3 && y > 4)                                                              // ���� ����� � ������ ����
            {
               whiteExp++;
            }
            whiteScore += 1 / sqrt((FIELD_SIZE - x) * (FIELD_SIZE - x) +  y * y);            // ���������� ����� ������� �� ������� ����� ����� �� ����
         }
         else if (checker->getColor() == BLACK)
         {
            if (x > 4 && y < 3)                                                              // ���� ����� � ������ ����
            {
               blackExp++;
            }

            blackScore += 1 / sqrt(x * x + (FIELD_SIZE / 2 - y) * (FIELD_SIZE / 2 - y));     // ���������� ����� ������� �� ������� ����� ����� �� ����
         }
      }
   }
   whiteScore = pow(whiteScore, whiteExp);                                                   // ���������� �� ������� � ����� ����
   blackScore = pow(blackScore, blackExp);
   return whiteScore - blackScore;
}

double Bot::miniMax(Field* field, int depth, bool maximazing)
{
   if (depth == 0 || field->checkWin(WHITE) || field->checkWin(BLACK) || field->checkLose(WHITE) || field->checkLose(BLACK)) // ���� ����� �� ����� ������ ��� �� ����� ����
   {
      return evaluation(field);             // ��������� ������� �� ����
   }
   double bestEval;
   Checker** checkers;
   if (maximazing)                          // �������������� ��������, ���� �������������
   {
      bestEval = -std::numeric_limits<double>::infinity();
      checkers = field->getCheckers(BLACK);
   }
   else                                     // � ���� ������������
   {
      bestEval = std::numeric_limits<double>::infinity();
      checkers = field->getCheckers(WHITE);
   }

   for (int i = 0; i < CHECKERS_COUNT; i++)// ���� ��� �������� �����, ��� � �-��� ����
   {
      Checker* checker = checkers[i];
      if (checker->getJumped())
      {
         List<Move> moves;
         field->generateMoves(checker, moves);
         for (int j = 0; j < moves.getLength(); j++)
         {
            Move move = moves.get(j);
            Field* editedField = field->copy();
            editedField->moveChecker(editedField->getCheckers(maximazing ? BLACK : WHITE)[i], move.x, move.y);
            double eval = miniMax(editedField, DEPTH, false);
            if (maximazing)
            {
               if (eval > bestEval)
               {
                  bestEval = eval;
               }
            }
            else
            {
               if (eval < bestEval)
               {
                  bestEval = eval;
               }
            }
            delete editedField;
         }
         return bestEval;
      }
   }
   for (int i = 0; i < CHECKERS_COUNT; i++)// ������������� ��� �����, ��� � �-��� ����
   {
      List<Move> moves;
      Checker* checker = checkers[i];
      field->generateMoves(checker, moves);
      for (int i = 0; i < moves.getLength(); i++)
      {
         Move move = moves.get(i);
         Field* editedField = field->copy();
         editedField->moveChecker(editedField->getCheckers(maximazing ? BLACK : WHITE)[i], move.x, move.y);
         double eval = miniMax(editedField, depth - 1, false);
         if (maximazing)
         {
            if (eval > bestEval)
            {
               bestEval = eval;
            }
         }
         else
         {
            if (eval < bestEval)
            {
               bestEval = eval;
            }
         }
         delete editedField;
      }
   }
   return bestEval;
}

double Bot::alphaBeta(Field* field, int depth, bool maximazing, double alpha, double beta)
{
   if (depth == 0 || field->checkWin(WHITE) || field->checkWin(BLACK) || field->checkLose(WHITE) || field->checkLose(BLACK)) // ���� ����� �� ����� ������ ��� �� ����� ����
   {
      return evaluation(field);              // ��������� ������� �� ����
   }
   double bestEval;
   Checker** checkers;
   if (maximazing)                          // �������������� ��������, ���� �������������
   {
      bestEval = -std::numeric_limits<double>::infinity();
      checkers = field->getCheckers(BLACK);
   }
   else                                     // � ���� ������������
   {
      bestEval = std::numeric_limits<double>::infinity();
      checkers = field->getCheckers(WHITE);
   }

   for (int i = 0; i < CHECKERS_COUNT; i++)// ���� ��� �������� �����, ��� � �-��� ����
   {
      Checker* checker = checkers[i];
      if (checker->getJumped())
      {
         List<Move> moves;
         field->generateMoves(checker, moves);
         for (int j = 0; j < moves.getLength(); j++)
         {
            Move move = moves.get(j);
            Field* editedField = field->copy();
            editedField->moveChecker(editedField->getCheckers(maximazing ? BLACK : WHITE)[i], move.x, move.y);
            double eval = alphaBeta(editedField, DEPTH, false, alpha, beta);
            if (maximazing)
            {
               if (eval > bestEval)
               {
                  bestEval = eval;
               }
               if (eval > alpha)
               {
                  alpha = eval;
               }
               if (beta <= alpha)
                  break;
            }
            else
            {
               if (eval < bestEval)
               {
                  bestEval = eval;
               }
               if (eval < beta)
               {
                  beta = eval;
               }
               if (beta <= alpha)
                  break;
            }
            delete editedField;
         }
         return bestEval;
      }
   }
   for (int i = 0; i < CHECKERS_COUNT; i++)// ������������� ��� �����, ��� � �-��� ����
   {
      List<Move> moves;
      Checker* checker = checkers[i];
      field->generateMoves(checker, moves);
      for (int i = 0; i < moves.getLength(); i++)
      {
         Move move = moves.get(i);
         Field* editedField = field->copy();
         editedField->moveChecker(editedField->getCheckers(maximazing ? BLACK : WHITE)[i], move.x, move.y);
         double eval = alphaBeta(editedField, depth - 1, false, alpha, beta);
         if (maximazing)
         {
            if (eval > bestEval)
            {
               bestEval = eval;
            }
            if (eval > alpha)
            {
               alpha = eval;
            }
            if (beta <= alpha)
               break;
         }
         else
         {
            if (eval < bestEval)
            {
               bestEval = eval;
            }
            if (eval < beta)
            {
               beta = eval;
            }
            if (beta <= alpha)
               break;
         }
         delete editedField;
      }
   }
   return bestEval;
}
