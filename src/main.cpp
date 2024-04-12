#include <SFML/Graphics.hpp>
#include "./headers/Constants.h"
#include "./headers/Game.h" 
#include "./headers/Button.h"

int main()
{
   sf::RenderWindow window(sf::VideoMode(DECK_SIZE, WINDOW_HEIGHT), "Corners", sf::Style::Titlebar | sf::Style::Close);// ���� ����
   Label messageLabel;                                                                                         // ������� ��� ������ ���������
   messageLabel.setup(100, 550);
   Button startButton(300, 550, "New game");
   Game game(&messageLabel);
   game.setup();                                                                                               // ������ ����
   while (window.isOpen())
   {
      sf::Event event;
      while (window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
         {
            window.close();
         }
         else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) // ���� �������� ����� ������� ����
         {
            if (startButton.handleClick(sf::Mouse::getPosition(window)))                                       // ���� �������� �� ������ ����� ����
            {
               game.setup();                                                                                   // �������� ������
            }
         }
      }
      window.clear(sf::Color::White);                                                                          // ������� ����
      game.update(window, event);                                                                              // ��������� ����
      game.draw(window);                                                                                       // ������������ ��� ��������
      startButton.draw(window);
      messageLabel.draw(window);
      window.display();                                                                                        // ���������� ��
   }
   return 0;
}

