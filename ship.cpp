#include <iostream>
#include <stdlib.h>
#include "ship.h"

using std::cout;
using std::to_string;

void Cell::set_x(int in_x)
{
	if(in_x < 0 || in_x >= FIELD_SIZE)
	{
		Error err;
		err.err_txt = "Ошибка в функции Cell::set_x. Недопустимое значение in_x = " + to_string(in_x);
		throw(err);		
	}
	x = in_x;
}

void Cell::set_y(int in_y)
{
	if(in_y < 0 || in_y >= FIELD_SIZE)
	{
		Error err;
		err.err_txt = "Ошибка в функции Cell::set_y. Недопустимое значение in_y = " + to_string(in_y);
		throw(err);		
	}
	y = in_y;
}

void Cell::set_val(cell_val in_val)
{
	if(in_val <= CELL_MIN || in_val >= CELL_MAX)
	{
		Error err;
		err.err_txt = "Ошибка в функции Cell::set_val. Недопустимое значение in_val = " + to_string(in_val);
		throw(err);
	}
	val = in_val;	
}

int Cell::get_x() const
{
	return x;
}

int Cell::get_y() const
{
	return y;
}

cell_val Cell::get_val() const
{
	return val;
}	


// --------------------- Ship ----------------------

void Ship::set_x(int in_x)
{
	if(in_x<0 || in_x>=FIELD_SIZE)
	{
		Error err;
		err.err_txt = "Ошибка в функции Ship::set_x. Недопустимое значение in_x = " + to_string(in_x);
		throw(err);		
	}
	
	x = in_x;
}

void Ship::set_y(int in_y)
{
	if(in_y<0 || in_y>=FIELD_SIZE)
	{
		Error err;
		err.err_txt = "Ошибка в функции Ship::set_y. Недопустимое значение in_y = " + to_string(in_y);
		throw(err);		
	}
	
	y = in_y;

}

void Ship::set_len(int in_len)
{
	if(in_len<1 || in_len>FIELD_SIZE)
	{
		Error err;
		err.err_txt = "Ошибка в функции Ship::set_len. Недопустимое значение in_len = " + to_string(in_len);
		throw(err);		
	}
	
	len = in_len;
}

void Ship::set_dir(direction in_dir)
{
	dir = in_dir;
}

int Ship::get_x() const
{
	return x;
}

int Ship::get_y() const
{
	return y;
}

int Ship::get_len() const
{
	return len;
}

direction Ship::get_dir() const
{
	return dir;
}	

/*

int Ship::set_pos(int x, int y, direction dir)
{
	if(dir == hor)
	{
		if(x<0 || x+ship_len>FIELD_SIZE || y<0 || y>FIELD_SIZE)
			return -1;
	}
	else
	{
		if(x<0 || x>FIELD_SIZE || y<0 || y+ship_len>FIELD_SIZE)
			return -1;	
	}
	
	ship_x = x;
	ship_y = y;
	ship_dir = dir;
	return 1;
}


int Ship::get_x() const
{
	return ship_x;
}

int Ship::get_y() const
{
	return ship_y;
}

int Ship::get_len() const
{
	return ship_len;
}

direction Ship::get_dir() const
{
	return ship_dir;
}

//-------------------- Fleet ------------------

Fleet::Fleet(vector<int> sh)
{
	num = sh.size();	
	ships = sh;
	
	en = new Enumerator(num, (FIELD_SIZE * FIELD_SIZE)*2);
}

Fleet::~Fleet()
{
	delete en;
}

int Fleet::set_pos(int x, int y, direction dir, int index)
{
	if(index < 0 || index > num)
	{
		cout << "Error Fleet::set_pos, index =" << index << endl;
		exit(0);
	}
	
	int state = pos_to_state(x,y,dir);
	
	en->set(index,state);
}

int Fleet::set_next_pos(bool is_good)
{
	int res;
	
	res = en->next(is_good);
	return res;
}

vector<Ship> Fleet::get_ships() //not coplete
{
	vector<Ship> tmp;
	int i;
	vector<int> state = en->get();
	

	for(i=0;i<num;i++)
	{
		if(state[i] > -1)
		{
			
		}
	}
}

int Fleet::pos_to_state(int x, int y, direction dir)
{
	if(x<0 || x>= FIELD_SIZE || y<0 || y>= FIELD_SIZE)
		cout << "Error Fleet::pos_to_state, x=" << x << ", y=" << y << ", dir=" << dir << endl;
	
	int st=0;
	
	st += x;
	st += y*FIELD_SIZE;
	st += ((int)dir) * FIELD_SIZE * FIELD_SIZE;
	
	return st;
}

int Fleet::state_to_x(int state)
{
	if(state < 0 || state >= 2 * FIELD_SIZE * FIELD_SIZE)
	{
		cout << "Error Fleet::state_to_x, state=" << state << endl;
		exit(0);
	}
	
	int x = state % FIELD_SIZE;
	return x;
}

int Fleet::state_to_y(int state)
{
	if(state < 0 || state >= 2 * FIELD_SIZE * FIELD_SIZE)
	{
		cout << "Error Fleet::state_to_y, state=" << state << endl;
		exit(0);
	}
	
	int y = (state/FIELD_SIZE) % FIELD_SIZE;
	return y;
}

direction Fleet::state_to_dir(int state)
{
	if(state < 0 || state >= 2 * FIELD_SIZE * FIELD_SIZE)
	{
		cout << "Error Fleet::state_to_dir, state=" << state << endl;
		exit(0);
	}
	
	int dir = (state/(FIELD_SIZE * FIELD_SIZE));
	return (direction)dir;
}
*/




