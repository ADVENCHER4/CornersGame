#pragma once
#include <SFML/Graphics.hpp>
#include "./Label.h"

class Button
{
private:
   sf::Color _color;                   // цвет фона кнопки
   sf::RectangleShape _shape;          // фон
   Label _label;                       // надпись
   int _width;                         // ширина
   int _height;                        // высота
   int _x;                             // позиция
   int _y;
public:  
   Button(int, int, const char*);      // конструктор
   void draw(sf::RenderWindow&);       // ф-ция отрисовки
   bool handleClick(sf::Vector2i);     // ф-ция обработки клика по кнопке
};