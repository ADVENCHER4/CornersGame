#include "../headers/Label.h"

Label::Label(): _x(0), _y(0)                    // �������������� �������
{
   _font.loadFromFile("D:\\Docs\\������\\2 ����\\TP\\CourseWork\\assets\\arial.ttf");
   _label.setFillColor(sf::Color::Black);
   _label.setFont(_font);
   _label.setCharacterSize(16);
}

void Label::setup(int x, int y)
{
   _x = x;                                      // ������ ����������  
   _y = y;
   _label.setPosition(_x + 10, _y + 5);         // ������ ���������� ������ � ��������
}

void Label::draw(sf::RenderWindow& window)
{
   window.draw(_label);
}

void Label::setText(const char* text)
{
   _label.setString(text);                      // ������ ����� ��� �������
}
