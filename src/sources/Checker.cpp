#include "../headers/Checker.h"

Checker::Checker(int x, int y, Color color) : _x(x), _y(y), _color(color), _selected(false), _hasMoves(false), _jumped(false)
{
   _shape.setRadius(CELL_SIZE / 2);                                           // �������������� �����
   _shape.setFillColor(_color ? sf::Color(200, 200, 200) : sf::Color::Black);
   _shape.setOutlineColor(sf::Color::Red);
}

void Checker::move(int x, int y)
{
   _x = x;                                               // ������ ����������
   _y = y;
}

void Checker::draw(sf::RenderWindow& window)
{
   int x = _x * CELL_SIZE + EDGE_SIZE;                   // ��������� ���������� ���� � ���������� ����
   int y = _y * CELL_SIZE + EDGE_SIZE;
   _shape.setPosition(sf::Vector2f(x, y));               // ������ ������� ��� ���������
   if (_selected)                                        // ���� ����� �������, ��������� �������
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
   return _jumped;                                 // ������ �� �����
}

Checker* Checker::copy()
{
   Checker* res = new Checker(_x, _y, _color);     // ������� ����� �����
   res->_jumped = _jumped;                         // ������ �� ��� �������� �������
   res->_hasMoves = _hasMoves;
   return res;
}

Checker::~Checker()
{
}



