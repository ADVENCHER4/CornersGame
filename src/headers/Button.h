#pragma once
#include <SFML/Graphics.hpp>
#include "./Label.h"

class Button
{
private:
   sf::Color _color;                   // ���� ���� ������
   sf::RectangleShape _shape;          // ���
   Label _label;                       // �������
   int _width;                         // ������
   int _height;                        // ������
   int _x;                             // �������
   int _y;
public:  
   Button(int, int, const char*);      // �����������
   void draw(sf::RenderWindow&);       // �-��� ���������
   bool handleClick(sf::Vector2i);     // �-��� ��������� ����� �� ������
};