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
	void out_coord() const;
	void in_coord() ;	
	void out_val() const;	
	void in_val();
	
	//делает первоначальную расстановку кораблей
	void init_ships();
	
	//вычисляет координаты ячейки в которую стреляет
	void shoot();	
	
	//добавляет результаты выстрела в my_shoots
	void update();

	//запрашивает значение ячейки из ships, добавляет в enemy_shoots
	void check();	
	
	//проверяет, не закончилась ли игра
	game_st get_status();

private:
	Field my_ships;			// Поле с нашими кораблями
	Field my_shoots;		// Поле с нашими выстрелами
	Field en_shoots;		// Поле с выстрелами соперника (enemy)
	
	Cell cell;				// Ячейка для передачи информации между функциями
};

#endif