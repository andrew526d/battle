#ifndef FIELD_H
#define FIELD_H 

#include <iostream>
#include <list>
#include "ship.h"

using std::list;
using std::ostream;
using std::cout;
using std::endl;

#define FIELD_SIZE 10

enum cell_val
{
	CELL_EMPTY,
	CELL_SHIP,
	CELL_UNKNOWN
};


/*
	Field for sea battle. Values for field cells:
	0 - empty
	1 - ship
	2 - unknown
*/


class Field
{
public:
	Field();
	
	int set_cell(int x, int y, cell_val val);
	int get_cell(int x, int y) const;
	
	int check_ships(const vector<Ship>& ships) const;
	int add_ship(const Ship& sh);						//1 if added, -1 if can't be added
	int add_ships(const vector<Ship>& ships);				//1 if added, -1 if can't be added, added all or nothing
	int try_add_ships(const vector<Ship>& ships);				//1 if added, -1 if can't be added, added until possible
	
	friend ostream& operator<<(ostream& cout, const Field& f);

private:
	int buf[FIELD_SIZE][FIELD_SIZE];

	
};


#endif