#include "../headers/Checker.h"

Checker::Checker(int x, int y, Color color) : _x(x), _y(y), _color(color), _selected(false), _hasMoves(false), _jumped(false)
{
   _shape.setRadius(CELL_SIZE / 2);                                           // инициализируем шашку
   _shape.setFillColor(_color ? sf::Color(200, 200, 200) : sf::Color::Black);
   _shape.setOutlineColor(sf::Color::Red);
}

void Checker::move(int x, int y)
{
   _x = x;                                               // задаем координаты
   _y = y;
}

void Checker::draw(sf::RenderWindow& window)
{
   int x = _x * CELL_SIZE + EDGE_SIZE;                   // переводим координаты окна в координаты поля
   int y = _y * CELL_SIZE + EDGE_SIZE;
   _shape.setPosition(sf::Vector2f(x, y));               // задаем позицию для отрисовки
   if (_selected)                                        // если шашка выбрана, добавляем обводку
   {
      _shape.setOutlineThickness(2.f);
   }
   else
   {
      _shape.setOutlineThickness(0.f);
   }

   window.draw(_shape);
}

sf::Vector2i Checker::getPosition()
{
   return sf::Vector2i(_x, _y);
}

Color Checker::getColor()
{
   return _color;
}

void Checker::select()
{
   _selected = true;
}

void Checker::deselect()
{
   _selected = false;
}

void Checker::setMovesAviability(bool hasMoves)
{
   _hasMoves = hasMoves;
}

bool Checker::getMovesAviability()
{
   return _hasMoves;
}

void Checker::setJumped(bool jumped)
{
   _jumped = jumped;
}

bool Checker::getJumped()
{
   return _jumped;                                 // ходила ли шашка
}

Checker* Checker::copy()
{
   Checker* res = new Checker(_x, _y, _color);     // создаем новую шашку
   res->_jumped = _jumped;                         // задаем ей все значения текущей
   res->_hasMoves = _hasMoves;
   return res;
}

Checker::~Checker()
{
}



