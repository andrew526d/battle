#include "field.h"
#include "ship.h"
#include <stdlib.h>


Field::Field()
{
	int i,j;
	for(i=0;i<FIELD_SIZE;i++)
		for(j=0;j<FIELD_SIZE;j++)
			buf[i][j] = CELL_UNKNOWN;
}

int Field::set_cell(int x, int y, cell_val val)
{
	if(x<0 || x>=FIELD_SIZE || y<0 || y>=FIELD_SIZE)
	{
		cout << "Error Field::set_cell, x = " << x << ", y = " << y << ", val = " << val << endl;
		exit(0);
	}
	
	buf[x][y] = val;
	return val;
}

int Field::get_cell(int x, int y) const
{
	if(x<0 || x>=FIELD_SIZE || y<FIELD_SIZE || y>=FIELD_SIZE)
	{
		cout << "Error Field::get_cell, x = " << x << ", y = " << y << endl;
		exit(0);
	}
	
	return buf[x][y];
	
}

int Field::add_ship(const Ship& sh)
{
	int x,y,len,i,j;
	direction dir;	
	int xmin, ymin, xmax, ymax;
	
	x = sh.get_x();
	y = sh.get_y();
	len = sh.get_len();
	dir = sh.get_dir();
	
	//  check possibility of adding ship
	if(dir == hor)
	{
		for(i=x;i<x+len;i++)
			if(buf[i][y] != CELL_UNKNOWN) return -1;
	}
	else
	{
		for(j=y;j<y+len;j++)
			if(buf[x][j] != CELL_UNKNOWN) return -1;
	}
	
	if(x==0) 
		xmin = 0;
	else
		xmin = x-1;
	
	if(y==0) 
		ymin = 0;
	else
		ymin = y-1;
	
	if(dir == hor)
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
	
	//cout << xmin << xmax << ymin << ymax  << endl;
	
	//    set empty sells
	for(i=xmin;i<=xmax;i++)
		for(j=ymin;j<=ymax;j++)
				buf[i][j] = CELL_EMPTY;
		
			
	//  set ship 
	if(dir == hor)
	{
		for(i=x;i<x+len;i++)
			buf[i][y] = CELL_SHIP;
	}
	else
	{
		for(j=y;j<y+len;j++)
			buf[x][j] = CELL_SHIP;
	}
	return 1;
}

int Field::try_add_ships(const vector<Ship>& ships)
{
	vector<Ship>::const_iterator it;
	int res;
	
	for(it = ships.begin(); it!=ships.end(); it++)
	{
		res = add_ship(*it);
		if(res == -1)
			return -1;
	}
	
	return 1;
}

int Field::check_ships(const vector<Ship>& ships) const
{
	Field tmp;
	tmp = *this;
	int res;
	
	res = tmp.try_add_ships(ships);
	return res;
}

int Field::add_ships(const vector<Ship>& ships)
{
	int res;
	
	res = check_ships(ships);
	if(res != -1)
		try_add_ships(ships);
	
	return res;
}

ostream& operator<<(ostream& out, const Field& f)
{
	int i,j;
	
	cout << "   ";
	for(i=0;i<FIELD_SIZE;i++)
		cout << i << " ";
	cout << endl;
	
	for(i=0;i<FIELD_SIZE;i++)
	{
		cout << i << "  ";
		for(j=0;j<FIELD_SIZE;j++)
		{
			switch(f.buf[j][i])
			{
				case CELL_EMPTY: out << "- "; break;
				case CELL_SHIP: out << "X "; break;
				default: out << ". ";
			}
		}
			out << endl;
	}
	
	return out;
}