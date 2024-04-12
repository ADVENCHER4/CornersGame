#pragma once
#include <SFML/Graphics.hpp>

class Label
{
private:
   int _x;                       // координаты
   int _y;                       
   sf::Text _label;              // надпись
   sf::Font _font;               // шрифт
public:
   Label();
   void setup(int, int);         // инициализация
   void draw(sf::RenderWindow&); // отрисовка
   void setText(const char*);    // задание текста
};