#pragma once
#include <SFML/Graphics.hpp>
#include "./Constants.h"
#include "./Checker.h"
#include "./List.h"

struct Move                                  // ���
{
   int x;                                    // ����������
   int y;
   bool shouldJump;                          // ����� �� ��� ���������� ���� �������
   Move() : x(0), y(0), shouldJump(false) {}
   Move(int _x, int _y, bool _shouldJump) : x(_x), y(_y), shouldJump(_shouldJump) {}
};

class Field
{
private:
   sf::Texture _deckTexture;                 // �������� ����
   sf::Sprite _deck;                         // ��� ����
   Checker* _field[FIELD_SIZE][FIELD_SIZE];  // ��� ������ ����
   Checker* _checkersWhite[CHECKERS_COUNT];  // ����� �����
   Checker* _checkersBlack[CHECKERS_COUNT];  // ������ �����
public:
   Field();
   void setup();                             // ������������� ����
   Checker* getChecker(int, int);            // ��������� ����� �� �����������
   bool moveChecker(Checker*, int, int);     // ����������� ����� �� �����������
   void generateMoves(Checker*, List<Move>&);// ��������� ����� ��� �����
   void draw(sf::RenderWindow&);             // �-��� ��������� �����
   bool checkWin(Color);                     // �������� �� ������
   bool checkLose(Color);                    // �������� �� ��������
   Field* copy();                            // ����������� ����
   Checker** getCheckers(Color);             // ��������� ����� �� �����
   ~Field();
};