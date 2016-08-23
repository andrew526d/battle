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
	my_ships.fill(CELL_UNKNOWN);
	my_shoots.fill(CELL_UNKNOWN);
	en_shoots.fill(CELL_UNKNOWN);
	
	live_ships = ship_types;
	my_ship_cells = 0;
	
	int i;
	for(i=0;i<ship_types.size();i++)
	{
		my_ship_cells += ship_types[i];
	}
	en_ship_cells = my_ship_cells;
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
				case CELL_WOUND: c = '+'; break;
				case CELL_KILL: c = 'X'; break;
				case CELL_MY_SHIP: c = 'S'; break;
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
				case CELL_WOUND: c = '+'; break;
				case CELL_KILL: c = 'X'; break;
				case CELL_MY_SHIP: c = 'S'; break;
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
				case CELL_WOUND: c = '+'; break;
				case CELL_KILL: c = 'X'; break;
				case CELL_MY_SHIP: c = 'S'; break;
				case CELL_UNKNOWN: c = '.'; break;
				default: c = '?';
			}
			cout << c << " ";
		}

		cout << endl;
	}
	cout << endl;	
}

void Game::out_coord(const Cell& cell) const
{
	char c1,c2;
	
	c1 = 'a' + cell.get_x();
	c2 = '0' + cell.get_y();
	
	cout << "Мой ход: " << c1 << c2 << endl;	
}

Cell Game::in_coord()
{
	string str;
	int x,y;
	char c1,c2;
	Cell cell;
	
	
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
				return cell;
			}
		}
	}
}	

void Game::out_val(cell_val val) const
{
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

cell_val Game::in_val()
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
			return (cell_val)val;
	};
	
}


void Game::init_ships()
{
	int i, j, val, len, psbl_count, select;
	vector<Ship> psbl;	//возможные расстановки кораблей
	Cell cell;
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
	
	// Заполняет CELL_EMPTY вместо CELL_UNKNOWN
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

Cell Game::shoot()
{
	Cell new_shoot;
	Cell wounded;
	
	if(my_shoots.get_wound(wounded))
		new_shoot = shoot_old(wounded);
	else
		new_shoot = shoot_new();
	
	return new_shoot;
}

Cell Game::shoot_new()
{
	int len; 			//длина самого большого корабля
	int i,j,k, psbl_count;
	vector<Ship> psbl;	//возможные расстановки кораблей
	Field F;
	Ship ship;
	cell_val val;
	Cell cell, tmp_cell;
	int count[FIELD_SIZE][FIELD_SIZE];
	
	len = get_max_ship();
	for(j=0;j<FIELD_SIZE;j++)
		for(k=0;k<FIELD_SIZE;k++)
			count[j][k] = 0;

	
	psbl = my_shoots.get_all_psbl(len);
	psbl_count = psbl.size();		
	for(i=0;i<psbl_count;i++)
	{
		F.fill(CELL_EMPTY);
		ship = psbl[i];
		F.add_ship(ship);
		for(j=0;j<FIELD_SIZE;j++)
			for(k=0;k<FIELD_SIZE;k++)
			{
				tmp_cell = F.get_cell(j,k);
				val = tmp_cell.get_val();
				if(val == CELL_MY_SHIP)
					count[j][k]++;
			}
	}
	
	int max_val = 0;
	for(j=0;j<FIELD_SIZE;j++)
		for(k=0;k<FIELD_SIZE;k++)
		{
			if(count[j][k]>max_val)
			{
				max_val = count[j][k];
				cell.set_x(j);
				cell.set_y(k);
			}
		}
	
	return cell;
}	

Cell Game::shoot_old(const Cell& prev)
{
	int x,y, flag_hor=0, flag_ver=0;
	Cell cell, tmp_cell;
	cell_val val;
	direction dir;
	
	// ---- проверяем есть ли еще ранения------
	if(get_left(prev) == CELL_WOUND || get_right(prev) == CELL_WOUND)
		flag_hor = 1;
	
	if(get_up(prev) == CELL_WOUND || get_down(prev) == CELL_WOUND)
		flag_ver = 1;
	


	//проверяем корректность
	if(flag_hor && flag_ver)
	{
		Error err;
		err.err_txt = "Ошибка в функции Game::shoot_old. Крестообразный корабль";
		throw(err);		
	}

	x = prev.get_x();
	y = prev.get_y();
	
	// ---------------- выбираем клетку ----------
	if(flag_hor)
	{
		cell.set_x(x);
		cell.set_y(y);
		
		while(get_left(cell) == CELL_WOUND) // двигаемся влево
		{
			x--;
			cell.set_x(x);
		}
		if(get_left(cell) == CELL_UNKNOWN)
		{
			x--;
			cell.set_x(x);
			return cell;
		}
		
		x = prev.get_x();
		cell.set_x(x);
		while(get_right(cell) == CELL_WOUND) // двигаемся вправо
		{
			x++;
			cell.set_x(x);
		}
		if(get_right(cell) == CELL_UNKNOWN)
		{
			x++;
			cell.set_x(x);
			return cell;
		}
		else
		{
			Error err;
			err.err_txt = "Ошибка в функции Game::shoot_old. Невозможно убить горизонтальный корабль";
			throw(err);		
		}
	}
	else if(flag_ver)						//вертикальный корабль
	{
		cell.set_x(x);
		cell.set_y(y);
		
		while(get_up(cell) == CELL_WOUND) // двигаемся влево
		{
			y--;
			cell.set_y(y);
		}
		if(get_up(cell) == CELL_UNKNOWN)
		{
			y--;
			cell.set_y(y);
			return cell;
		}
		
		y = prev.get_y();
		cell.set_y(y);
		while(get_down(cell) == CELL_WOUND) // двигаемся вправо
		{
			y++;
			cell.set_y(y);
		}
		if(get_down(cell) == CELL_UNKNOWN)
		{
			y++;
			cell.set_y(y);
			return cell;
		}
		else
		{
			Error err;
			err.err_txt = "Ошибка в функции Game::shoot_old. Невозможно убить горизонтальный корабль";
			throw(err);		
		}
	}
	else		// неизвестно направление корабля
	{
		if(get_left(prev) == CELL_UNKNOWN)
		{
			cell.set_x(x-1);
			cell.set_y(y);
			return cell;
		}
		else if(get_up(prev) == CELL_UNKNOWN)
		{
			cell.set_x(x);
			cell.set_y(y-1);
			return cell;
		}
		else if(get_right(prev) == CELL_UNKNOWN)
		{
			cell.set_x(x+1);
			cell.set_y(y);
			return cell;
		}
		else if(get_down(prev) == CELL_UNKNOWN)
		{
			cell.set_x(x);
			cell.set_y(y+1);
			return cell;
		}
		else
		{
			Error err;
			err.err_txt = "Ошибка в функции Game::shoot_old. Ранен одноклеточный корабль";
			throw(err);		

		}
	}

	
}
	
void Game::update(const Cell& cell)
{
	cell_val val;
	int len;
	
	val = cell.get_val();
	if(val == CELL_EMPTY)
		my_shoots.set_cell(cell);
	else if(val == CELL_WOUND)
	{
		my_shoots.set_cell(cell);
		en_ship_cells --;
	}
	else if(val == CELL_KILL)
	{
		len = my_shoots.kill(cell);
		del_ship(len);
		en_ship_cells --;
	}
	else
	{
		Error err;
		err.err_txt = "Ошибка в функции Game::update. Недопустимое значение val = " + to_string(val);
		throw(err);
	
	}
}
	
cell_val Game::check(const Cell& cell)
{
	cell_val val;
	Cell tmp_cell;
	int x,y,res;
	
	x = cell.get_x();
	y = cell.get_y();
	
	tmp_cell = my_ships.get_cell(x,y);
	val = tmp_cell.get_val();
	
	if(val == CELL_EMPTY)
	{
		en_shoots.set_cell(tmp_cell);
		return CELL_EMPTY;
	}
	else if(val == CELL_MY_SHIP)
	{
		my_ship_cells --;
		tmp_cell.set_val(CELL_WOUND);
		my_ships.set_cell(tmp_cell);
		res = my_ships.is_killed(tmp_cell);
		if(res == true)
		{
			tmp_cell.set_val(CELL_KILL);
			en_shoots.kill(tmp_cell);
			my_ships.kill(tmp_cell);
			return CELL_KILL;
		}
		else
		{
			tmp_cell.set_val(CELL_WOUND);
			en_shoots.set_cell(tmp_cell);
			return CELL_WOUND;
		}
		
	}
	else
	{
		Error err;
		err.err_txt = "Ошибка в функции Game::update. Недопустимое значение val = " + to_string(val);
		throw(err);
	
	}
}	

int Game::get_max_ship() const
{
	int i,num,len=0;
	
	num = live_ships.size();
	for(i=0;i<num;i++)
	{
		if(live_ships[i]>len)
			len = live_ships[i];
	}
	return len;
}

void Game::del_ship(int len)
{
	int i,num;
	
	num = live_ships.size();
	for(i=0;i<num;i++)
	{
		if(live_ships[i] == len)
		{
			live_ships[i] = 0;
			return;
		}
	}
	
	Error err;
	err.err_txt = "Ошибка в функции Game::del_ship. Недопустимое невозможно удалить корабль с длиной " + to_string(len);
	throw(err);

}

game_st Game::get_status()
{
	 if(my_ship_cells <=0)
	 {
		 cout << "Вы выиграли!" << endl;
		 return GAME_LOOSE;
	 }
	 else if(en_ship_cells <=0)
	 {
		 cout << "Вы проиграли!" << endl;
		 return GAME_WIN;
	 }
	 
	 return GAME_UNKNOWN;

}

cell_val Game::get_left(const Cell& cell)
{
	int x,y;
	Cell tmp_cell;
	
	x = cell.get_x();
	y = cell.get_y();
	
	if(x==0)
		return CELL_EMPTY;
	else
	{
		tmp_cell = my_shoots.get_cell(x-1,y);
		return tmp_cell.get_val();
	}		
}

cell_val Game::get_right(const Cell& cell)
{
	int x,y;
	Cell tmp_cell;
	
	x = cell.get_x();
	y = cell.get_y();
	
	if(x==FIELD_SIZE-1)
		return CELL_EMPTY;
	else
	{
		tmp_cell = my_shoots.get_cell(x+1,y);
		return tmp_cell.get_val();
	}
}

cell_val Game::get_up(const Cell& cell)
{
	int x,y;
	Cell tmp_cell;
	
	x = cell.get_x();
	y = cell.get_y();
	
	if(y==0)
		return CELL_EMPTY;
	else
	{
		tmp_cell = my_shoots.get_cell(x,y-1);
		return tmp_cell.get_val();
	}	
}

cell_val Game::get_down(const Cell& cell)
{
	int x,y;
	Cell tmp_cell;
	
	x = cell.get_x();
	y = cell.get_y();
	
	if(y==FIELD_SIZE-1)
		return CELL_EMPTY;
	else
	{
		tmp_cell = my_shoots.get_cell(x,y+1);
		return tmp_cell.get_val();
	}
}
