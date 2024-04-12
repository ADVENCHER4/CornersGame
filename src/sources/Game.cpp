#include "../headers/Game.h"

Game::Game(Label* label) : _selectedChecker(nullptr), _isPlayerMove(true), _playerColor(WHITE), _botColor(BLACK), _hasGameEnded(false), _playerMovesCount(0), _botMovesCount(0), _messageLabel(label)
{
}

void Game::setup()
{
   _messageLabel->setText("");         // обнуляем поля класса
   _playerMovesCount = 0;
   _botMovesCount = 0;
   _selectedChecker = nullptr;
   _isPlayerMove = true;
   _hasGameEnded = false;
   _field.setup();                     // настраиваем игровое поле
}

void Game::update(sf::RenderWindow& window, sf::Event& event)
{
   if (_hasGameEnded)                  // если игра окончена
      return;
   if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)   // если кликнули левой кнопкой мыши
   {
      handleClick(sf::Mouse::getPosition(window));
   }
   if (!_isPlayerMove)                 // если не ход игрока
   {
      makeBotMove();
   }
}
void Game::handleClick(sf::Vector2i position)
{
   if (position.x < EDGE_SIZE || position.x > DECK_SIZE - EDGE_SIZE || position.y < EDGE_SIZE || position.y > DECK_SIZE - EDGE_SIZE)   // если кликнули вне доски
      return;
   if (_isPlayerMove)                  // если ход игрока
   {
      makePlayerMove(position);
   }
}
void Game::makePlayerMove(sf::Vector2i position)
{
   position.x = (position.x - EDGE_SIZE) / CELL_SIZE;                      // получаем координаты клика
   position.y = (position.y - EDGE_SIZE) / CELL_SIZE;
   Checker* checker = _field.getChecker(position.x, position.y);           // получаем по этим координатам шашку
   if (checker && checker->getColor() != _playerColor)                     // если есть шашка и она не игрока
      return;
   if (!_selectedChecker && checker)                                       // если есть шашка и до этого не выбрали шашку
   {
      _selectedChecker = checker;                                          // выбираем её
      _selectedChecker->select();
   }
   else if (_selectedChecker && checker && !_selectedChecker->getJumped()) // если есть шашка, до этого выбрали шашку но не ходили ей
   {
      _selectedChecker->deselect();
      _selectedChecker = checker;
      _selectedChecker->select();
   }
   else if (_selectedChecker && !checker)                                  // если выбрали шашку и кликнули по пустому месту
   {
      bool isSuccess = _field.moveChecker(_selectedChecker, position.x, position.y);// пытаемся сходить в эту точку
      if (!isSuccess)                                                      // если не получилось, завершаем ход без перехода очереди
      {
         return;
      }
      if (_playerMovesCount >= LOSE_MOVES_COUNT && _field.checkLose(_playerColor))// если сходили достаточно ходов для проигрыша и проиграли
      {
         _hasGameEnded = true;                                             // заканчиваем игру
         _messageLabel->setText("White lose");
      }
      else if (_field.checkWin(_playerColor))                              // если выиграли
      {
         _hasGameEnded = true;                                             // заканчиваем игру
         _messageLabel->setText("White wins");
      }
      if (_selectedChecker->getMovesAviability())                          // если шашка прыгала и может прыгнуть еще
         return;                                                           // завершаем ход без перехода очереди
      _playerMovesCount++;                                                 // прибавляем кол-во ходов
      _selectedChecker->setJumped(false);                                  // обнуляем все значения
      _selectedChecker->deselect();
      _selectedChecker = nullptr;
      _isPlayerMove = false;                                               // передаем ход
   }
}

void Game::makeBotMove()
{
   MoveVariant variant = _bot.chooseMove(&_field);                          // выбираем ход
   bool isSuccess = _field.moveChecker(variant._checker, variant._move.x, variant._move.y);// пытаемся сходить
   if (!isSuccess)                                                         // дальнейший код аналогичен коду для хода игрока за исключением цвета шашки
      return;
   if (_botMovesCount >= LOSE_MOVES_COUNT && _field.checkLose(_botColor))
   {
      _hasGameEnded = true;
      _messageLabel->setText("Black lose");
   }
   else if (_field.checkWin(_botColor))
   {
      _hasGameEnded = true;
      _messageLabel->setText("Black wins");
   }
   if (variant._checker->getMovesAviability())
      return;
   _botMovesCount++;
   variant._checker->setJumped(false);
   variant._checker->deselect();
   _isPlayerMove = true;

}

void Game::showMessage(sf::Text label, const char* text)
{
   label.setString(text);
}

void Game::draw(sf::RenderWindow& window)
{
   _field.draw(window);
}