#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "const.h"
#include "ship.h"
#include "field.h"


// Класс, реализующий контекст игры и пользовательский интерфейс
class Game
{
	
public:
	Game();
	~Game();
	
	//выводит на экран поля	
	void out_fields() const;					
	  
	//выводит и запрашивает координаты и значение ячейки
	void out_coord() const;
	void in_coord() const;	
	void out_val();	
	void in_val();
	
	//вычисляет координаты ячейки в которую стреляет
	void shoot();	
	
	//добавляет результаты выстрела в our_shoots
	void set_cell();

	//запрашивает значение ячейки из ships, добавляет в enemy_shoots
	void get_cell();	
	
	//проверяет, не закончилась ли игра
	game_st check_status();

private:
	FieldShips ships;			// Поле с нашими кораблями
	FieldEmpty our_shoots;		// Поле с нашими выстрелами
	FieldEmpty enemy_shoots;	// Поле с выстрелами соперника
};

#endif