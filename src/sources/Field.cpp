#include "../headers/Field.h"

bool Field::moveChecker(Checker* checker, int x, int y)
{
   bool canMove = false;                        // можем ли сходить в заданную точку
   List<Move> moves;                            // список возможных ходов
   Move move;                                   // текущий ход
   generateMoves(checker, moves);               // получаем возможные ходы
   for (int i = 0; i < moves.getLength(); i++)  // проверяем, есть ли среди них выбранный
   {
      move = moves.get(i);
      if (move.x == x && move.y == y)
      {
         canMove = true;
         break;
      }
   }
   if (canMove)                                 // если можем сходить по заданным координтам
   {
      _field[y][x] = _field[checker->getPosition().y][checker->getPosition().x]; // передвигаем шашку
      _field[checker->getPosition().y][checker->getPosition().x] = nullptr;      // зануляем её прошлую позицию
      checker->move(x, y);                      // передвигаем её для отрисовки
      checker->setJumped(move.shouldJump);      // прыгала ли шашка
      if (move.shouldJump)                      // если прыгала
      {
         List<Move> jumpMoves;                  // ходы, в которые она может прыгнуть
         generateMoves(checker, jumpMoves);
         checker->setMovesAviability(jumpMoves.getLength() > 0); // есть ли возможность продолжать прыжки
      }
   }
   return canMove;                              // успешен ли был ход
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
   sf::Vector2i position = checker->getPosition();    // получаем координаты шашки
   if (checker->getJumped())                          // если ходила
   {
      if (checker->getColor() == WHITE)               // если белая, то может двигаться вверх и вправо
      {
         // если может прыгнуть вправо
         if (position.x + 2 < FIELD_SIZE && _field[position.y][position.x + 1] && !_field[position.y][position.x + 2])
         {
            moves.add(Move(position.x + 2, position.y, true));
         }
         // если может прыгнуть вверх
         if (position.y - 2 >= 0 && _field[position.y - 1][position.x] && !_field[position.y - 2][position.x])
         {
            moves.add(Move(position.x, position.y - 2, true));
         }
      }
      else if (checker->getColor() == BLACK)          // если черная, то может двигаться вниз и влево
      {
         // если может прыгнуть влево
         if (position.x - 2 >= 0 && _field[position.y][position.x - 1] && !_field[position.y][position.x - 2])
         {
            moves.add(Move(position.x - 2, position.y, true));
         }
         // если может прыгнуть вниз
         if (position.y + 2 < FIELD_SIZE && _field[position.y + 1][position.x] && !_field[position.y + 2][position.x])
         {
            moves.add(Move(position.x, position.y + 2, true));
         }
      }
   }
   else                                               // если не ходила
   {
      if (checker->getColor() == WHITE)
      {
         if (position.x + 1 < FIELD_SIZE && !_field[position.y][position.x + 1])     // если может сходить вправо
         {
            moves.add(Move(position.x + 1, position.y, false));
         }
         else if (position.x + 2 < FIELD_SIZE && !_field[position.y][position.x + 2])// или прыгнуть вправо
         {
            moves.add(Move(position.x + 2, position.y, true));
         }
         if (position.y - 1 >= 0 && !_field[position.y - 1][position.x])             // если может сходить вверх
         {
            moves.add(Move(position.x, position.y - 1, false));
         }
         else if (position.y - 2 >= 0 && !_field[position.y - 2][position.x])        // или прыгнуть вверх
         {
            moves.add(Move(position.x, position.y - 2, true));
         }
      }
      else if (checker->getColor() == BLACK)
      {
         if (position.x - 1 >= 0 && !_field[position.y][position.x - 1])             // если может сходить влево
         {
            moves.add(Move(position.x - 1, position.y, false));
         }
         else if (position.x - 2 >= 0 && !_field[position.y][position.x - 2])        // или прыгнуть влево
         {
            moves.add(Move(position.x - 2, position.y, true));
         }
         if (position.y + 1 < FIELD_SIZE && !_field[position.y + 1][position.x])     // если может сходить вниз
         {
            moves.add(Move(position.x, position.y + 1, false));
         }
         else if (position.y + 2 < FIELD_SIZE && !_field[position.y + 2][position.x])// или прыгнуть вниз
         {
            moves.add(Move(position.x, position.y + 2, true));
         }
      }
   }
}


Field::Field()
{
   _deckTexture.loadFromFile("D:\\Docs\\Универ\\2 курс\\TP\\CourseWork\\assets\\deck.png");
   _deck.setTexture(_deckTexture);
   for (int i = 0; i < FIELD_SIZE; i++)                                                // обнуляем клетки поля
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
   for (int i = 0; i < FIELD_SIZE; i++)                                                // проверяем все клетки
   {
      for (int j = 0; j < FIELD_SIZE; j++)
      {
         if (_field[i][j])                                                             // если что-то есть, удаляем
            delete _field[i][j];
         _field[i][j] = nullptr;                                                       // зануляем клетку
      }
   }
   for (int i = 0; i < CHECKERS_COUNT; i++)                                            // заполняем нижний угол белыми шашками
   {
      Checker* checker = new Checker(BOTTOM_CORNER[i][0], BOTTOM_CORNER[i][1], WHITE);
      _checkersWhite[checkersNum] = checker;
      _field[BOTTOM_CORNER[i][1]][BOTTOM_CORNER[i][0]] = checker;
      checkersNum++;
   }
   checkersNum = 0;
   for (int i = 0; i < CHECKERS_COUNT; i++)                                            // заполняем верхний угол черными шашками
   {
      Checker* checker = new Checker(TOP_CORNER[i][0], TOP_CORNER[i][1], BLACK);
      _checkersBlack[checkersNum] = checker;
      _field[TOP_CORNER[i][1]][TOP_CORNER[i][0]] = checker;
      checkersNum++;
   }
}

Checker* Field::getChecker(int x, int y)
{
   return _field[y][x];                                                                // возвращаем шашку по координатам
}

bool Field::checkWin(Color checkersColor)
{
   if (checkersColor == WHITE)                                                         // если проверяем для белых
   {
      for (int i = 0; i < CHECKERS_COUNT; i++)
      {
         Checker* checker = getChecker(TOP_CORNER[i][0], TOP_CORNER[i][1]);            // проверяем все шашки из верхнего угла
         if (!checker || checker->getColor() != WHITE)                                 // если пусто или шашка не белая, то не победа
            return false;
      }
   }
   else if (checkersColor == BLACK)                                                    // если проверяем для черных
   {
      for (int i = 0; i < CHECKERS_COUNT; i++)                                         
      {  
         Checker* checker = getChecker(BOTTOM_CORNER[i][0], BOTTOM_CORNER[i][1]);      // проверяем все шашки из нижнего угла
         if (!checker || checker->getColor() != BLACK)                                 // если пусто или шашка не черная, то не победа
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
         Checker* checker = getChecker(BOTTOM_CORNER[i][0], BOTTOM_CORNER[i][1]);      // проверяем нижний угол
         if (checker && checker->getColor() == WHITE)                                  // если есть белая шашка, то проигрыш
            return true;
      }
   }
   else if (checkersColor == BLACK)
   {
      for (int i = 0; i < CHECKERS_COUNT; i++)
      {
         Checker* checker = getChecker(TOP_CORNER[i][0], TOP_CORNER[i][1]);            // проверяем верхний угол
         if (checker && checker->getColor() == BLACK)                                  // если есть черная шашка, то проигрыш
            return true;
      }
   }
   return false;
}

Field* Field::copy()
{
   Field* res = new Field();                             // создаем новое поле
   int whiteNum = 0;
   int blackNum = 0;
   for (int i = 0; i < FIELD_SIZE; i++)                  // копируем все элементы доски в новое поле
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
   if (color == BLACK)                             // возвращаем шашки соответствующего цвета
      return _checkersBlack;
   return _checkersWhite;
}

Field::~Field()
{
   for (int i = 0; i < CHECKERS_COUNT; i++)        // очищаем память
   {
      delete _checkersWhite[i];
      delete _checkersBlack[i];
   }
}