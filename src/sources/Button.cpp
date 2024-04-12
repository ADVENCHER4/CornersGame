#include "../headers/Button.h"

Button::Button(int x, int y, const char* text) : _width(100), _height(30), _x(x), _y(y)
{
   _color = sf::Color(200, 200, 200);                 // инициализируем значения
   _shape.setSize(sf::Vector2f(_width, _height));
   _shape.setFillColor(_color);
   _shape.setPosition(_x, _y);
   _label.setup(x, y);
   _label.setText(text);
}

void Button::draw(sf::RenderWindow& window)
{
   window.draw(_shape);                               // рисуем фон и надпись
   _label.draw(window);
}

bool Button::handleClick(sf::Vector2i position)
{
   return position.x >= _x && position.x <= _x + _width && position.y >= _y && position.y <= _y + _height;// в пределах ли кнопки нажатие
}
