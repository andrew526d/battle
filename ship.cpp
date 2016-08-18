#include <iostream>
#include <stdlib.h>
#include "ship.h"
#include "field.h"


Ship::Ship(int len)
{
	if(len<1 || len>FIELD_SIZE)
	{
		cout << "Error: Ship::Ship, len = " << len << endl;
		exit(0);
	}
	
	ship_x = 0;
	ship_y = 0;
	ship_len = len;
	ship_dir = hor;
}

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





