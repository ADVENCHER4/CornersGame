#pragma once
#include <SFML/Graphics.hpp>
#include "./Field.h"
#include "./Checker.h"
#include "./Label.h"
#include "./Bot.h"

class Game
{
private:
   Field _field;                                // поле
   Checker* _selectedChecker;                   // выбранна€ шашка
   Bot _bot;                                     // бот
   bool _isPlayerMove;                          // ходит ли игрок
   bool _hasGameEnded;                          // закончилась ли игра
   Color _playerColor;                          // цвет игрока
   Color _botColor;                             // цвет бота
   Label* _messageLabel;                        // надпись дл€ вывода сообщений о победе/проигрыше
   int _playerMovesCount;                       // кол-во ходов
   int _botMovesCount;
   
   void handleClick(sf::Vector2i);              // обработчик клика
   void makePlayerMove(sf::Vector2i);           // ход игрока
   void makeBotMove();                          // ход компьютера
   void showMessage(sf::Text, const char*);     // вывод сообщени€
public:
   Game(Label*);                                // конструктора
   void setup();                                // инициализаци€ игры
   void update(sf::RenderWindow&, sf::Event&);  // обновление состо€ни€ игры
   void draw(sf::RenderWindow&);                // ф-ци€ отрисовки игры
};