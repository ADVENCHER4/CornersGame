#include "../headers/Field.h"

bool Field::moveChecker(Checker* checker, int x, int y)
{
   bool canMove = false;                        // ����� �� ������� � �������� �����
   List<Move> moves;                            // ������ ��������� �����
   Move move;                                   // ������� ���
   generateMoves(checker, moves);               // �������� ��������� ����
   for (int i = 0; i < moves.getLength(); i++)  // ���������, ���� �� ����� ��� ���������
   {
      move = moves.get(i);
      if (move.x == x && move.y == y)
      {
         canMove = true;
         break;
      }
   }
   if (canMove)                                 // ���� ����� ������� �� �������� ����������
   {
      _field[y][x] = _field[checker->getPosition().y][checker->getPosition().x]; // ����������� �����
      _field[checker->getPosition().y][checker->getPosition().x] = nullptr;      // �������� � ������� �������
      checker->move(x, y);                      // ����������� � ��� ���������
      checker->setJumped(move.shouldJump);      // ������� �� �����
      if (move.shouldJump)                      // ���� �������
      {
         List<Move> jumpMoves;                  // ����, � ������� ��� ����� ��������
         generateMoves(checker, jumpMoves);
         checker->setMovesAviability(jumpMoves.getLength() > 0); // ���� �� ����������� ���������� ������
      }
   }
   return canMove;                              // ������� �� ��� ���
}

void Field::draw(sf::RenderWindow& window)
{
   window.draw(_deck);
   for (int i = 0; i < CHECKERS_COUNT; i++)
   {
      _checkersWhite[i]->draw(window);
      _checkersBlack[i]->draw(window);
   }
}
void Field::generateMoves(Checker* checker, List<Move>& moves)
{
   sf::Vector2i position = checker->getPosition();    // �������� ���������� �����
   if (checker->getJumped())                          // ���� ������
   {
      if (checker->getColor() == WHITE)               // ���� �����, �� ����� ��������� ����� � ������
      {
         // ���� ����� �������� ������
         if (position.x + 2 < FIELD_SIZE && _field[position.y][position.x + 1] && !_field[position.y][position.x + 2])
         {
            moves.add(Move(position.x + 2, position.y, true));
         }
         // ���� ����� �������� �����
         if (position.y - 2 >= 0 && _field[position.y - 1][position.x] && !_field[position.y - 2][position.x])
         {
            moves.add(Move(position.x, position.y - 2, true));
         }
      }
      else if (checker->getColor() == BLACK)          // ���� ������, �� ����� ��������� ���� � �����
      {
         // ���� ����� �������� �����
         if (position.x - 2 >= 0 && _field[position.y][position.x - 1] && !_field[position.y][position.x - 2])
         {
            moves.add(Move(position.x - 2, position.y, true));
         }
         // ���� ����� �������� ����
         if (position.y + 2 < FIELD_SIZE && _field[position.y + 1][position.x] && !_field[position.y + 2][position.x])
         {
            moves.add(Move(position.x, position.y + 2, true));
         }
      }
   }
   else                                               // ���� �� ������
   {
      if (checker->getColor() == WHITE)
      {
         if (position.x + 1 < FIELD_SIZE && !_field[position.y][position.x + 1])     // ���� ����� ������� ������
         {
            moves.add(Move(position.x + 1, position.y, false));
         }
         else if (position.x + 2 < FIELD_SIZE && !_field[position.y][position.x + 2])// ��� �������� ������
         {
            moves.add(Move(position.x + 2, position.y, true));
         }
         if (position.y - 1 >= 0 && !_field[position.y - 1][position.x])             // ���� ����� ������� �����
         {
            moves.add(Move(position.x, position.y - 1, false));
         }
         else if (position.y - 2 >= 0 && !_field[position.y - 2][position.x])        // ��� �������� �����
         {
            moves.add(Move(position.x, position.y - 2, true));
         }
      }
      else if (checker->getColor() == BLACK)
      {
         if (position.x - 1 >= 0 && !_field[position.y][position.x - 1])             // ���� ����� ������� �����
         {
            moves.add(Move(position.x - 1, position.y, false));
         }
         else if (position.x - 2 >= 0 && !_field[position.y][position.x - 2])        // ��� �������� �����
         {
            moves.add(Move(position.x - 2, position.y, true));
         }
         if (position.y + 1 < FIELD_SIZE && !_field[position.y + 1][position.x])     // ���� ����� ������� ����
         {
            moves.add(Move(position.x, position.y + 1, false));
         }
         else if (position.y + 2 < FIELD_SIZE && !_field[position.y + 2][position.x])// ��� �������� ����
         {
            moves.add(Move(position.x, position.y + 2, true));
         }
      }
   }
}


Field::Field()
{
   _deckTexture.loadFromFile("D:\\Docs\\������\\2 ����\\TP\\CourseWork\\assets\\deck.png");
   _deck.setTexture(_deckTexture);
   for (int i = 0; i < FIELD_SIZE; i++)                                                // �������� ������ ����
   {
      for (int j = 0; j < FIELD_SIZE; j++)
      {
         _field[i][j] = nullptr;
      }
   }
}

void Field::setup()
{
   int checkersNum = 0;
   for (int i = 0; i < FIELD_SIZE; i++)                                                // ��������� ��� ������
   {
      for (int j = 0; j < FIELD_SIZE; j++)
      {
         if (_field[i][j])                                                             // ���� ���-�� ����, �������
            delete _field[i][j];
         _field[i][j] = nullptr;                                                       // �������� ������
      }
   }
   for (int i = 0; i < CHECKERS_COUNT; i++)                                            // ��������� ������ ���� ������ �������
   {
      Checker* checker = new Checker(BOTTOM_CORNER[i][0], BOTTOM_CORNER[i][1], WHITE);
      _checkersWhite[checkersNum] = checker;
      _field[BOTTOM_CORNER[i][1]][BOTTOM_CORNER[i][0]] = checker;
      checkersNum++;
   }
   checkersNum = 0;
   for (int i = 0; i < CHECKERS_COUNT; i++)                                            // ��������� ������� ���� ������� �������
   {
      Checker* checker = new Checker(TOP_CORNER[i][0], TOP_CORNER[i][1], BLACK);
      _checkersBlack[checkersNum] = checker;
      _field[TOP_CORNER[i][1]][TOP_CORNER[i][0]] = checker;
      checkersNum++;
   }
}

Checker* Field::getChecker(int x, int y)
{
   return _field[y][x];                                                                // ���������� ����� �� �����������
}

bool Field::checkWin(Color checkersColor)
{
   if (checkersColor == WHITE)                                                         // ���� ��������� ��� �����
   {
      for (int i = 0; i < CHECKERS_COUNT; i++)
      {
         Checker* checker = getChecker(TOP_CORNER[i][0], TOP_CORNER[i][1]);            // ��������� ��� ����� �� �������� ����
         if (!checker || checker->getColor() != WHITE)                                 // ���� ����� ��� ����� �� �����, �� �� ������
            return false;
      }
   }
   else if (checkersColor == BLACK)                                                    // ���� ��������� ��� ������
   {
      for (int i = 0; i < CHECKERS_COUNT; i++)                                         
      {  
         Checker* checker = getChecker(BOTTOM_CORNER[i][0], BOTTOM_CORNER[i][1]);      // ��������� ��� ����� �� ������� ����
         if (!checker || checker->getColor() != BLACK)                                 // ���� ����� ��� ����� �� ������, �� �� ������
            return false;
      }
   }
   return true;
}

bool Field::checkLose(Color checkersColor)
{
   if (checkersColor == WHITE)
   {
      for (int i = 0; i < CHECKERS_COUNT; i++)
      {
         Checker* checker = getChecker(BOTTOM_CORNER[i][0], BOTTOM_CORNER[i][1]);      // ��������� ������ ����
         if (checker && checker->getColor() == WHITE)                                  // ���� ���� ����� �����, �� ��������
            return true;
      }
   }
   else if (checkersColor == BLACK)
   {
      for (int i = 0; i < CHECKERS_COUNT; i++)
      {
         Checker* checker = getChecker(TOP_CORNER[i][0], TOP_CORNER[i][1]);            // ��������� ������� ����
         if (checker && checker->getColor() == BLACK)                                  // ���� ���� ������ �����, �� ��������
            return true;
      }
   }
   return false;
}

Field* Field::copy()
{
   Field* res = new Field();                             // ������� ����� ����
   int whiteNum = 0;
   int blackNum = 0;
   for (int i = 0; i < FIELD_SIZE; i++)                  // �������� ��� �������� ����� � ����� ����
   {
      for (int j = 0; j < FIELD_SIZE; j++)
      {
         if (_field[j][i])
         {
            Checker* checker = _field[j][i]->copy();
            res->_field[j][i] = checker;
            if (checker->getColor() == WHITE)
            {
               res->_checkersWhite[whiteNum] = checker;
               whiteNum++;
            }
            else
            {
               res->_checkersBlack[blackNum] = checker;
               blackNum++;
            }
         }
         else
         {
            res->_field[j][i] = nullptr;
         }
      }
   }
   return res;
}

Checker** Field::getCheckers(Color color)
{
   if (color == BLACK)                             // ���������� ����� ���������������� �����
      return _checkersBlack;
   return _checkersWhite;
}

Field::~Field()
{
   for (int i = 0; i < CHECKERS_COUNT; i++)        // ������� ������
   {
      delete _checkersWhite[i];
      delete _checkersBlack[i];
   }
}