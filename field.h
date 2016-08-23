#ifndef FIELD_H
#define FIELD_H 

#include <iostream>
#include "const.h"
#include "ship.h"

using std::ostream;
using std::cout;
using std::endl;


class Field
{
public:
	Field();
	~Field(){};

	void fill(cell_val val);						//Заполняет поле значением val
	void set_cell(const Cell& cell);
	Cell get_cell(int in_x, int in_y) const;
	vector<Ship> get_all_psbl(int len);				//возвращает все валидные варианты размещения корабля длины len
	void add_ship(const Ship &ship);	//добавляет корабль на поле
	bool is_killed(const Cell& cell);				//Проверяет, убит ли корабль
	int kill(const Cell& cell);						//Оформляет убитый корабль, возвращает его длину
	bool get_wound(Cell &cell);						//Находит клетку CELL_WOUND

private:
	bool check_ship(const Ship& ship);					//true если корабль может быть размещен
	cell_val buf[FIELD_SIZE][FIELD_SIZE];
};




#endif