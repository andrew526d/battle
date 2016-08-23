#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "const.h"
#include "ship.h"
#include "field.h"

using std::vector;


// Класс, реализующий контекст игры и пользовательский интерфейс
class Game
{
	
public:
	Game();
	~Game();
	
	//выводит на экран поля	
	void out_fields() const;
	void out_my_ships() const;
	  
	//выводит и запрашивает координаты и значение ячейки
	void out_coord(const Cell& cell) const;
	Cell in_coord() ;	
	void out_val(cell_val val) const;	
	cell_val in_val();
	
	//делает первоначальную расстановку кораблей
	void init_ships();
	
	//вычисляет координаты ячейки в которую стреляет.
	Cell shoot();	
	
	//вычисляет координаты нового корабля
	Cell shoot_new();	

	//вычисляет координаты старого корабля
	Cell shoot_old(const Cell& cell);	

	
	//добавляет результаты выстрела в my_shoots
	void update(const Cell& cell);

	//запрашивает значение ячейки из ships, добавляет в enemy_shoots
	cell_val check(const Cell& cell);	
	
	//проверяет, не закончилась ли игра
	game_st get_status();

private:
	Field my_ships;			// Поле с нашими кораблями
	Field my_shoots;		// Поле с нашими выстрелами
	Field en_shoots;		// Поле с выстрелами соперника (enemy)
	void del_ship(int len);	// Удаляет из live_ships корабль длины len;
	int get_max_ship() const;		// Возращает длину самого большого живого корабля
	
	//Возвращает значения соседних ячеек
	cell_val get_left(const Cell& cell);
	cell_val get_right(const Cell& cell);
	cell_val get_up(const Cell& cell);
	cell_val get_down(const Cell& cell);
	
	
	vector<int> live_ships;	// Оставшиеся в живых корабли
	int my_ship_cells;		// Всего занятых клеток нашими кораблями
	int en_ship_cells;		// Всего занятых клеток вражескими кораблями
};

#endif