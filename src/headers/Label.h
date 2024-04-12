#pragma once
#include <SFML/Graphics.hpp>

class Label
{
private:
   int _x;                       // ����������
   int _y;                       
   sf::Text _label;              // �������
   sf::Font _font;               // �����
public:
   Label();
   void setup(int, int);         // �������������
   void draw(sf::RenderWindow&); // ���������
   void setText(const char*);    // ������� ������
};