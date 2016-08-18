#ifndef SHIP_H
#define SHIP_H
#include "const.h"

class Cell
{

private:
	int x;
	int y;
	int val;
};

/*
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
*/

#endif