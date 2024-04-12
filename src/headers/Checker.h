#pragma once
#include <SFML/Graphics.hpp>
#include "../headers/Constants.h"

enum Color								// ����� �����
{
	BLACK,
	WHITE,
};

class Checker
{
private:
	int _x;								// �������
	int _y;
	Color _color;						// ����
	sf::CircleShape _shape;			// �����
	bool _selected;					// ������� �� �����
	bool _jumped;						// ������� ��
	bool _hasMoves;					// ���� �� ���� ����� ������

public:
   Checker(int, int, Color);		// �����������
	void move(int, int);				// �-��� �����������
	void draw(sf::RenderWindow&);	// �-��� ���������
	sf::Vector2i getPosition();	// ��������� �������
	Color getColor();					// ��������� �����
	void select();						// ����� �����
	void deselect();					// ������ ������
	void setMovesAviability(bool);// ������� ������� �����
	bool getMovesAviability();		// ��������� ������� �����
	void setJumped(bool);			// ������� ��������� ������
	bool getJumped();					// ��������� ����� ���������
	Checker* copy();					// ����������� �����
	~Checker();
};