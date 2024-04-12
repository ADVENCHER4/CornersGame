#pragma once
#include <SFML/Graphics.hpp>
#include "./Field.h"
#include "./Checker.h"
#include "./Label.h"
#include "./Bot.h"

class Game
{
private:
   Field _field;                                // ����
   Checker* _selectedChecker;                   // ��������� �����
   Bot _bot;                                     // ���
   bool _isPlayerMove;                          // ����� �� �����
   bool _hasGameEnded;                          // ����������� �� ����
   Color _playerColor;                          // ���� ������
   Color _botColor;                             // ���� ����
   Label* _messageLabel;                        // ������� ��� ������ ��������� � ������/���������
   int _playerMovesCount;                       // ���-�� �����
   int _botMovesCount;
   
   void handleClick(sf::Vector2i);              // ���������� �����
   void makePlayerMove(sf::Vector2i);           // ��� ������
   void makeBotMove();                          // ��� ����������
   void showMessage(sf::Text, const char*);     // ����� ���������
public:
   Game(Label*);                                // ������������
   void setup();                                // ������������� ����
   void update(sf::RenderWindow&, sf::Event&);  // ���������� ��������� ����
   void draw(sf::RenderWindow&);                // �-��� ��������� ����
};