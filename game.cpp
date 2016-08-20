#include "game.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::stoi;
using std::to_string;

Game::Game()
{
	cell.set_x(0);
	cell.set_y(0);
	cell.set_val(CELL_UNKNOWN);
	
	my_ships.fill(CELL_UNKNOWN);
	my_shoots.fill(CELL_UNKNOWN);
	en_shoots.fill(CELL_UNKNOWN);
}

Game::~Game()
{
	
}

void Game::out_fields() const
{
	int i,j;
	cell_val val;
	
	char c;
	
	cout << endl;
	cout << "      Мои корабли                Ваши корабли    " << endl;
	cout << "  a b c d e f g h i j        a b c d e f g h i j " << endl;
	for(i=0;i<FIELD_SIZE;i++)
	{
		cout << i << " ";
		for(j=0;j<FIELD_SIZE;j++)
		{
			val = en_shoots.get_cell(j,i).get_val();
			switch(val)
			{
				case CELL_EMPTY: c = '-'; break;
				case CELL_WOUND: c = 'X'; break;
				case CELL_KILL: c = 'X'; break;
				case CELL_UNKNOWN: c = '.'; break;
				default: c = '?';
			}
			cout << c << " ";
		}
		
		cout <<  "     " << i << " ";
		for(j=0;j<FIELD_SIZE;j++)
		{
			val = my_shoots.get_cell(j,i).get_val();
			switch(val)
			{
				case CELL_EMPTY: c = '-'; break;
				case CELL_WOUND: c = 'X'; break;
				case CELL_KILL: c = 'X'; break;
				case CELL_UNKNOWN: c = '.'; break;
				default: c = '?';
			}
			cout << c << " ";
		}

		cout << endl;
	}
	cout << endl;
}				

void Game::out_my_ships() const
{
	int i,j;
	cell_val val;
	
	char c;
	
	cout << endl;
	cout << "  a b c d e f g h i j " << endl;
	for(i=0;i<FIELD_SIZE;i++)
	{
		cout << i << " ";
		for(j=0;j<FIELD_SIZE;j++)
		{
			val = my_ships.get_cell(j,i).get_val();
			switch(val)
			{
				case CELL_EMPTY: c = '-'; break;
				case CELL_MY_SHIP: c = 'X'; break;
				case CELL_UNKNOWN: c = '.'; break;
				default: c = '?';
			}
			cout << c << " ";
		}

		cout << endl;
	}
	cout << endl;	
}

void Game::out_coord() const
{
	char c1,c2;
	
	c1 = 'a' + cell.get_x();
	c2 = '0' + cell.get_y();
	
	cout << "Мой ход: " << c1 << c2 << endl;	
}

void Game::in_coord()
{
	string str;
	int x,y;
	char c1,c2;
	
	
	cout << "Ваш ход: ";
	
	
	while(1)
	{
		cin >> str;
		if(str.size()!=2)
		{
			cout << "Неверное значение" << endl;
		}
		else
		{
			c1 = str[0] - 'a';
			c2 = str[1] - '0';
			
			if(c1 < 0 || c1 > FIELD_SIZE || c1 < 0 || c2 > FIELD_SIZE)
			{
				cout << "Неверное значение" << endl;
				continue;
			}
			else
			{
				cell.set_x(c1);
				cell.set_y(c2);
				break;
			}
		}
	}
}	

void Game::out_val() const
{
	cell_val val;
	val = cell.get_val();
	
	switch(val)
	{
		case CELL_EMPTY: cout << "Мимо" << endl; break;
		case CELL_WOUND: cout << "Ранил" << endl; break;
		case CELL_KILL: cout << "Убил" << endl; break;
		default:
		{
			Error err;
			err.err_txt = "Ошибка в функции Game::out_val. Недопустимое значение cell.getval() = " + to_string(val);
			throw(err);
		}
	}
}

void Game::in_val()
{
	string str;
	int val = -1;
	
	cout << "Введите результат: (";
	cout << "Мимо: " << CELL_EMPTY << ", ";
	cout << "Ранил: " << CELL_WOUND << ", ";
	cout << "Убил: " << CELL_KILL << "): ";
	
	
	while(1)
	{
		cin >> str;
		try
		{
			val = stoi(str);
		}
		catch(...)
		{
			cout << "Неверное значение" << endl;
			continue;
		}
		if(val != CELL_EMPTY && val != CELL_WOUND && val != CELL_KILL)
		{
			cout << "Неверное значение" << endl;
		}
		else
		{
			cell.set_val((cell_val)val);
			break;
		}
	};
	
}


void Game::init_ships()
{
	int i, j, val, len, psbl_count, select;
	vector<Ship> psbl;	//возможные расстановки кораблей
	Ship ship;
	
	for(i=0;i<ship_types.size();i++)
	{
		len = ship_types[i];
		psbl = my_ships.get_all_psbl(len);
		psbl_count = psbl.size();		
		select = rand() % psbl_count;
		ship = psbl[select];
		my_ships.add_ship(ship);
	}
	
	for(i=0;i<FIELD_SIZE;i++)
		for(j=0;j<FIELD_SIZE;j++)
		{
			cell = my_ships.get_cell(i,j);
			if(cell.get_val() == CELL_UNKNOWN)
			{
				cell.set_val(CELL_EMPTY);
				my_ships.set_cell(cell);
			}
		}
	
}


void Game::shoot()
{
	
}	
	
	
void Game::update()
{
	my_shoots.set_cell(cell);
}
	
void Game::check()
{
	en_shoots.set_cell(cell);
}	
	
game_st Game::get_status()
{
	 
}