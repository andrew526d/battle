#include <iostream>
#include <vector>
#include "enumerator.h"
#include "ship.h"
#include "field.h"

using std::cout;
using std::vector;

int main() 
{
	int x,y,state;
	direction dir;
	
	vector<int> ships;
	ships.push_back(3);
	
	Fleet f(ships);
	
	//----------------------
	x = 9; y = 9; dir = ver;
	cout << x << "  " << y << "  " << dir << endl;
	state = f.pos_to_state(x,y,dir);
	
	x = f.state_to_x(state);
	y = f.state_to_y(state);
	dir = f.state_to_dir(state);
	
	cout << x << "  " << y << "  " << dir << endl;
	

	return 0;
}