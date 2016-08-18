#ifndef SHIP_H
#define SHIP_H
#include <iostream>
#include <vector>
#include "enumerator.h"

using std::cout;
using std::endl;
using std::vector;
using std::ostream;


/*
	Class ship represents one ship
*/

enum direction	//direction (horizontal or vertical)
{
	hor,
	ver
};			


class Ship
{
public:
	Ship(int len);		// from 1 to FIELD_SIZE-1

	int set_pos(int x, int y, direction dir);
	int set_len(int len);	
	
	int get_x() const;
	int get_y() const;
	int get_len() const;
	direction get_dir() const;
private:
	int ship_x;			//x coordiname
	int ship_y;			//y coordinate
	int ship_len;		//length
	direction ship_dir;	//direction
};

class Fleet
{
public:
	Fleet(vector<int>);
	~Fleet();
	
	int set_pos(int x, int y, direction dir, int index);
	int set_next_pos(bool is_good);
	vector<Ship> get_ships();

	int state_to_x(int state);
	int state_to_y(int state);
	direction state_to_dir(int state);
	int pos_to_state(int x, int y, direction dir);
	
private:
	int num;
	vector<int> ships;
	Enumerator *en;
};

#endif