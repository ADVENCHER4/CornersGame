#include "../headers/Game.h"

Game::Game(Label* label) : _selectedChecker(nullptr), _isPlayerMove(true), _playerColor(WHITE), _botColor(BLACK), _hasGameEnded(false), _playerMovesCount(0), _botMovesCount(0), _messageLabel(label)
{
}

void Game::setup()
{
   _messageLabel->setText("");         // �������� ���� ������
   _playerMovesCount = 0;
   _botMovesCount = 0;
   _selectedChecker = nullptr;
   _isPlayerMove = true;
   _hasGameEnded = false;
   _field.setup();                     // ����������� ������� ����
}

void Game::update(sf::RenderWindow& window, sf::Event& event)
{
   if (_hasGameEnded)                  // ���� ���� ��������
      return;
   if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)   // ���� �������� ����� ������� ����
   {
      handleClick(sf::Mouse::getPosition(window));
   }
   if (!_isPlayerMove)                 // ���� �� ��� ������
   {
      makeBotMove();
   }
}
void Game::handleClick(sf::Vector2i position)
{
   if (position.x < EDGE_SIZE || position.x > DECK_SIZE - EDGE_SIZE || position.y < EDGE_SIZE || position.y > DECK_SIZE - EDGE_SIZE)   // ���� �������� ��� �����
      return;
   if (_isPlayerMove)                  // ���� ��� ������
   {
      makePlayerMove(position);
   }
}
void Game::makePlayerMove(sf::Vector2i position)
{
   position.x = (position.x - EDGE_SIZE) / CELL_SIZE;                      // �������� ���������� �����
   position.y = (position.y - EDGE_SIZE) / CELL_SIZE;
   Checker* checker = _field.getChecker(position.x, position.y);           // �������� �� ���� ����������� �����
   if (checker && checker->getColor() != _playerColor)                     // ���� ���� ����� � ��� �� ������
      return;
   if (!_selectedChecker && checker)                                       // ���� ���� ����� � �� ����� �� ������� �����
   {
      _selectedChecker = checker;                                          // �������� �
      _selectedChecker->select();
   }
   else if (_selectedChecker && checker && !_selectedChecker->getJumped()) // ���� ���� �����, �� ����� ������� ����� �� �� ������ ��
   {
      _selectedChecker->deselect();
      _selectedChecker = checker;
      _selectedChecker->select();
   }
   else if (_selectedChecker && !checker)                                  // ���� ������� ����� � �������� �� ������� �����
   {
      bool isSuccess = _field.moveChecker(_selectedChecker, position.x, position.y);// �������� ������� � ��� �����
      if (!isSuccess)                                                      // ���� �� ����������, ��������� ��� ��� �������� �������
      {
         return;
      }
      if (_playerMovesCount >= LOSE_MOVES_COUNT && _field.checkLose(_playerColor))// ���� ������� ���������� ����� ��� ��������� � ���������
      {
         _hasGameEnded = true;                                             // ����������� ����
         _messageLabel->setText("White lose");
      }
      else if (_field.checkWin(_playerColor))                              // ���� ��������
      {
         _hasGameEnded = true;                                             // ����������� ����
         _messageLabel->setText("White wins");
      }
      if (_selectedChecker->getMovesAviability())                          // ���� ����� ������� � ����� �������� ���
         return;                                                           // ��������� ��� ��� �������� �������
      _playerMovesCount++;                                                 // ���������� ���-�� �����
      _selectedChecker->setJumped(false);                                  // �������� ��� ��������
      _selectedChecker->deselect();
      _selectedChecker = nullptr;
      _isPlayerMove = false;                                               // �������� ���
   }
}

void Game::makeBotMove()
{
   MoveVariant variant = _bot.chooseMove(&_field);                          // �������� ���
   bool isSuccess = _field.moveChecker(variant._checker, variant._move.x, variant._move.y);// �������� �������
   if (!isSuccess)                                                         // ���������� ��� ���������� ���� ��� ���� ������ �� ����������� ����� �����
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