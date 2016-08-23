#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::srand;
using std::time;

int main()
{
	Game game;
	Cell my_shoot, en_shoot;
	srand(time(0));
	cell_val my_res, en_res;
	
	try
	{
		game.init_ships();
		game.out_my_ships();
		
		while(1)
		{
			game.out_my_ships();
			// Наш выстрел
			game.out_fields();		
			my_shoot = game.shoot();		
			game.out_coord(my_shoot);		
			my_res = game.in_val();
			my_shoot.set_val(my_res);
			game.update(my_shoot);
			if(game.get_status() == GAME_WIN)
				break;

		
			// Выстрел соперника
			game.out_fields();
			en_shoot = game.in_coord();		
			en_res = game.check(en_shoot);
			game.out_val(en_res);		
			if(game.get_status() == GAME_LOOSE)
				break;		
		}
	}
	
	catch(Error err)
	{
		cout << "Сбой в программе: " << err.err_txt << endl;
	}
	
	return 0;
}