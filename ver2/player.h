#ifndef PLAYER_H
#define PLAYER_H
#include "common.h"

// Интерфейс взаимодействия с игроком
class Player
{
public:
	virtual Cell ask_cell() = 0;				//Запросить выстрел у игрока
	virtual cell_val ask_val(Cell cell) = 0;	//Запросить результаты выстрела у игрока
	virtual void send_val(cell_val val) = 0;	//Передать игроку результаты выстрела
};

class Player_SSH: public Player
{
public:
	Cell ask_cell();
	cell_val ask_val(Cell cell);
	void send_val(cell_val val);
};

#endif 