#include <SFML/Graphics.hpp>
#include "./headers/Constants.h"
#include "./headers/Game.h" 
#include "./headers/Button.h"

int main()
{
   sf::RenderWindow window(sf::VideoMode(DECK_SIZE, WINDOW_HEIGHT), "Corners", sf::Style::Titlebar | sf::Style::Close);// окно игры
   Label messageLabel;                                                                                         // надпись для вывода сообщений
   messageLabel.setup(100, 550);
   Button startButton(300, 550, "New game");
   Game game(&messageLabel);
   game.setup();                                                                                               // запуск игры
   while (window.isOpen())
   {
      sf::Event event;
      while (window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
         {
            window.close();
         }
         else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) // если кликнули левой кнопкой мыши
         {
            if (startButton.handleClick(sf::Mouse::getPosition(window)))                                       // если кликнули на кнопку новой игры
            {
               game.setup();                                                                                   // начинаем заново
            }
         }
      }
      window.clear(sf::Color::White);                                                                          // очищаем окно
      game.update(window, event);                                                                              // обновляем игру
      game.draw(window);                                                                                       // отрисовываем все элементы
      startButton.draw(window);
      messageLabel.draw(window);
      window.display();                                                                                        // отображаем их
   }
   return 0;
}

