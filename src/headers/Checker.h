#pragma once
#include <SFML/Graphics.hpp>
#include "../headers/Constants.h"

enum Color								// цвета шашек
{
	BLACK,
	WHITE,
};

class Checker
{
private:
	int _x;								// позиция
	int _y;
	Color _color;						// цвет
	sf::CircleShape _shape;			// форма
	bool _selected;					// выбрана ли шашка
	bool _jumped;						// прыгала ли
	bool _hasMoves;					// есть ли ходы после прыжка

public:
   Checker(int, int, Color);		// конструктор
	void move(int, int);				// ф-ция перемещения
	void draw(sf::RenderWindow&);	// ф-ция отрисовки
	sf::Vector2i getPosition();	// получение позиции
	Color getColor();					// получение цвета
	void select();						// выбор шашки
	void deselect();					// отмена выбора
	void setMovesAviability(bool);// задание наличия ходов
	bool getMovesAviability();		// получение наличия ходов
	void setJumped(bool);			// задание состояния прыжка
	bool getJumped();					// получение этого состояния
	Checker* copy();					// копирование шашки
	~Checker();
};