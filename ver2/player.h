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
	
	//Обработка ошибок
	virtual void bad_cell(Cell cell) = 0;
	virtual void bad_val(Cell cell, cell_val val) = 0;
	
	//Конец игры
	virtual void win() = 0;
	virtual void lose() = 0;
};

class Player_TCP: public Player
{
public: 
	Player_TCP(int port);
	~Player_TCP();
	Cell ask_cell();
	cell_val ask_val(Cell cell);
	void send_val(cell_val val);

	void bad_cell(Cell cell);
	void bad_val(Cell cell, cell_val val);
	
	//Конец игры
	void win();
	void lose();	
	
private:
	void print(string msg);

	int port;
	int srv_sock;
	int cl_sock;
	
};

#endif 