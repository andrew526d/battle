#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::srand;
using std::time;

int main()
{
	Game game;
	srand(time(0));
	
	try
	{
		game.init_ships();
		game.out_my_ships();
		
		while(1)
		{
			// Наш выстрел
			game.out_fields();		
			game.shoot();		
			game.out_coord();		
			game.in_val();	
			game.update();
			if(game.get_status() == GAME_WIN)
				break;

		
			// Выстрел соперника
			game.out_fields();
			game.in_coord();		
			game.check();
			game.out_val();		
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