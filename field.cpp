#include "field.h"
#include <stdlib.h>
#include <string>

using std::string;
using std::to_string;

Field::Field()
{

}

void Field::fill(cell_val val)
{
	int i,j;
	for(i=0;i<FIELD_SIZE;i++)
		for(j=0;j<FIELD_SIZE;j++)
			buf[i][j] = val;
}

void Field::set_cell(const Cell& cell)
{
	int x,y;
	cell_val val;
	
	x = cell.get_x();
	y = cell.get_y();
	val = cell.get_val();
	
	buf[x][y] = val;
}

Cell Field::get_cell(int x, int y) const
{
	Cell cell;
	
	if(x<0 || x>=FIELD_SIZE || y<0 || y>=FIELD_SIZE)
	{
		Error err;
		err.err_txt = "Ошибка в функции Field::get_cell. Недопустимое значение: x = " + to_string(x) + ", y = " + to_string(y);
		throw(err);
	}
	
	cell.set_x(x);
	cell.set_y(y);
	cell.set_val(buf[x][y]);
	return cell;
}

vector<Ship> Field::get_all_psbl(int len)
{
	vector<Ship> psbl;
	Ship ship;
	int i,j;
	
	ship.set_len(len);
	
	for(i=0;i<FIELD_SIZE;i++)
		for(j=0;j<FIELD_SIZE;j++)
		{	
			ship.set_x(i);
			ship.set_y(j);

			ship.set_dir(DIR_HOR);
			if(check_ship(ship))
				psbl.push_back(ship);

			ship.set_dir(DIR_VER);
			if(check_ship(ship))
				psbl.push_back(ship);			
			
		}
		
	return psbl;
}

void Field::add_ship(const Ship& ship)
{
	int x,y,len,i,j;
 	direction dir;	
 	int xmin, ymin, xmax, ymax;
 
	x = ship.get_x();
	y = ship.get_y();
	len = ship.get_len();
	dir = ship.get_dir();
	
 	if(x==0) 
 		xmin = 0;
 	else
 		xmin = x-1;
 	
 	if(y==0) 
 		ymin = 0;
 	else
 		ymin = y-1;
 	
 	if(dir == DIR_HOR)
 	{
 		if(x+len == FIELD_SIZE)
 			xmax = x+len-1;
 		else
 			xmax = x+len;
 		
 		if(y == FIELD_SIZE-1)
 			ymax = y;
 		else
 			ymax = y+1;
 	}
 	else
 	{
 		if(x == FIELD_SIZE-1)
 			xmax = x;
 		else
 			xmax = x+1;
 		
 		if(y+len == FIELD_SIZE)
 			ymax = y+len-1;
 		else
 			ymax = y+len;
 	}
	
 	//    set empty sells
 	for(i=xmin;i<=xmax;i++)
 		for(j=ymin;j<=ymax;j++)
 				buf[i][j] = CELL_EMPTY;
 		
 			
 	//  set ship 
 	if(dir == DIR_HOR)
 	{
 		for(i=x;i<x+len;i++)
 			buf[i][y] = CELL_MY_SHIP;
 	}
 	else
 	{
 		for(j=y;j<y+len;j++)
 			buf[x][j] = CELL_MY_SHIP;
 	}

}

bool Field::check_ship(const Ship& ship)
{
	int i,j,x,y,len;
	direction dir;
	
	x = ship.get_x();
	y = ship.get_y();
	len = ship.get_len();
	dir = ship.get_dir();
	
	if(x<0 || y<0 || x>=FIELD_SIZE || y>=FIELD_SIZE)
		return false;
	
	if(dir == DIR_HOR)
 	{
		if(x+len > FIELD_SIZE)
			return false;
		
 		for(i=x;i<x+len;i++)
 			if(buf[i][y] != CELL_UNKNOWN) 
				return false;
 	}
 	else
 	{
		if(y+len > FIELD_SIZE)
			return false;

 		for(j=y;j<y+len;j++)
 			if(buf[x][j] != CELL_UNKNOWN) 
				return false;
 	}
	return true;
}


bool Field::is_killed(const Cell& cell)
{
	int x,y;
	
	// проверяем слева
	x = cell.get_x();
	y = cell.get_y();
	while(buf[x][y] != CELL_EMPTY && x>0)
	{
		x--;
		if(buf[x][y] == CELL_MY_SHIP)
			return false;
	}
	
	// проверяем справа
	x = cell.get_x();
	y = cell.get_y();
	while(buf[x][y] != CELL_EMPTY && x<FIELD_SIZE-1)
	{
		x++;
		if(buf[x][y] == CELL_MY_SHIP)
			return false;
	}
	
	// проверяем сверху
	x = cell.get_x();
	y = cell.get_y();
	while(buf[x][y] != CELL_EMPTY && y>0)
	{
		y--;
		if(buf[x][y] == CELL_MY_SHIP)
			return false;
	}
	
	// проверяем справа
	x = cell.get_x();
	y = cell.get_y();
	while(buf[x][y] != CELL_EMPTY && y<FIELD_SIZE-1)
	{
		y++;
		if(buf[x][y] == CELL_MY_SHIP)
			return false;
	}

	return true;
	
}


int Field::kill(const Cell& cell)
{	
	int x,y,len=1,flag_x=0, flag_y=0;
	int x_min, y_min;
	direction dir;
	Ship ship;
	
	// проверяем слева
	x = cell.get_x();
	y = cell.get_y();
	x_min = x;
	y_min = y;
	while(buf[x][y] != CELL_EMPTY && x>0)
	{
		x--;
		if(buf[x][y] == CELL_WOUND)
		{
			len++;
			dir = DIR_HOR;
			x_min = x;
			flag_x = 1;
		}
	}
	
	// проверяем справа
	x = cell.get_x();
	y = cell.get_y();
	while(buf[x][y] != CELL_EMPTY && x<FIELD_SIZE-1)
	{
		x++;
		if(buf[x][y] == CELL_WOUND)
		{
			len++;
			dir = DIR_HOR;
			flag_x = 1;
		}
	}
	
	// проверяем сверху
	x = cell.get_x();
	y = cell.get_y();
	while(buf[x][y] != CELL_EMPTY && y>0)
	{
		y--;
		if(buf[x][y] == CELL_WOUND)
		{
			len++;
			dir = DIR_VER;
			y_min = y;
			flag_y = 1;
		}
	}
	
	// проверяем снизу
	x = cell.get_x();
	y = cell.get_y();
	while(buf[x][y] != CELL_EMPTY && y<FIELD_SIZE-1)
	{
		y++;
		if(buf[x][y] == CELL_WOUND)
		{
			len++;
			dir = DIR_VER;
			flag_y = 1;
		}
	}
	
	if(flag_x && flag_y)
	{
		Error err;
		err.err_txt = "Ошибка в функции Field::kill. Крестообразный корабль";
		throw(err);
		
	}
	
	//  ---- добавляем корабль ----------------
	ship.set_x(x_min);
	ship.set_y(y_min);
	ship.set_len(len);
	ship.set_dir(dir);
	
	cout << x_min << y_min << " " << len << endl;
	add_ship(ship);

	int i,j;
	for(i=0;i<FIELD_SIZE;i++)
		for(j=0;j<FIELD_SIZE;j++)
			if(buf[i][j] == CELL_MY_SHIP)
				buf[i][j] = CELL_KILL;
		
	return len;
}

bool Field::get_wound(Cell &cell)
{
	int i,j;
	
	for(i=0;i<FIELD_SIZE;i++)
		for(j=0;j<FIELD_SIZE;j++)
		{
			if(buf[i][j] == CELL_WOUND)
			{
				cell.set_x(i);
				cell.set_y(j);
				cell.set_val(CELL_WOUND);
				return true;
			}
		}
		
	return false;
}
