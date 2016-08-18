#ifndef CONST_H
#define CONST_H
// --------------- Константы и макросы ---------

#define FIELD_SIZE 10	//Размер поля

enum cell_val			//Возможные значения клеток
{
	CELL_EMPTY,
	CELL_WOUND,
	CELL_KILL,
	CELL_UNKNOWN
};

enum direction			//Направление корабля (вертикальное или горизонтальное)
{
	DIR_HOR,
	DIR_VER
};	
 
enum game_st			//статус игры
{
	GAME_UNKNOWN,
	GAME_WIN,
	GAME_LOOSE
};

#endif		
