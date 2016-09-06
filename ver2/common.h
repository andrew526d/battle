#ifndef COMMON_H
#define COMMON_H

struct Cell
{
	int x;
	int y;
};

enum cell_val			//Возможные значения клеток
{
	CELL_EMPTY,
	CELL_WOUND,
	CELL_KILL,
	CELL_SHIP,			//нетронутая клетка корабля
	CELL_UNKNOWN,
	CELL_MIN = CELL_EMPTY,
	CELL_MAX = CELL_UNKNOWN
};


#endif