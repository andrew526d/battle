#ifndef CONST_H
#define CONST_H
#include <string>
#include <vector>

using std::string;
using std::vector;

// --------------- Константы и макросы ---------

#define FIELD_SIZE 10	//Размер поля

const extern vector<int> ship_types;




// -------------- Exception Class -------------
struct Error
{
	string err_txt;
};


enum cell_val			//Возможные значения клеток
{
	CELL_MIN,
	CELL_EMPTY,
	CELL_WOUND,
	CELL_KILL,
	CELL_MY_SHIP,
	CELL_UNKNOWN,
	CELL_MAX
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
