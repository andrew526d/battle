#include "game.h"

int main()
{
	Game game;
	
	while(1)
	{
		// наш выстрел
		game.out_fields();		
		game.shoot();		
		game.out_coord();		
		game.in_val();	
		game.set_cell();
		if(game.check_status() == GAME_WIN)
			break;
 
		
		// выстрел соперника
		game.out_fields();
		game.in_coord();		
		game.get_cell();
		game.out_val();		
		game.check_status();
		if(game.check_status() == GAME_LOOSE)
			break;		
	}
	
}