#pragma once
#include <SFML/Graphics.hpp>
#include "./Constants.h"
#include "./Checker.h"
#include "./List.h"

struct Move                                  // ход
{
   int x;                                    // координаты
   int y;
   bool shouldJump;                          // нужно ли для совершения хода прыгать
   Move() : x(0), y(0), shouldJump(false) {}
   Move(int _x, int _y, bool _shouldJump) : x(_x), y(_y), shouldJump(_shouldJump) {}
};

class Field
{
private:
   sf::Texture _deckTexture;                 // текстура поля
   sf::Sprite _deck;                         // фон поля
   Checker* _field[FIELD_SIZE][FIELD_SIZE];  // все ячейки поля
   Checker* _checkersWhite[CHECKERS_COUNT];  // белые шашки
   Checker* _checkersBlack[CHECKERS_COUNT];  // черные шашки
public:
   Field();
   void setup();                             // инициализация поля
   Checker* getChecker(int, int);            // получение шашки по координатам
   bool moveChecker(Checker*, int, int);     // перемещение шашки по координатам
   void generateMoves(Checker*, List<Move>&);// генерация ходов для шашки
   void draw(sf::RenderWindow&);             // ф-ция отрисовки шашки
   bool checkWin(Color);                     // проверка на победу
   bool checkLose(Color);                    // проверка на проигрыш
   Field* copy();                            // копирование поля
   Checker** getCheckers(Color);             // получение шашек по цвету
   ~Field();
};