#include "player.h"


int main()
{
	Player_SSH Player1;
	Player_SSH Player2;
	Cell cell;
	cell_val val;
	
	while(1)
	{
		//  стреляет первый игрок
		cell = Player1.ask_cell();
		val = Player2.ask_val(cell);
		Player1.send_val(val);
		
		//  стреляет второй игрок
		cell = Player2.ask_cell();
		val = Player1.ask_val(cell);
		Player2.send_val(val);
	}
} 
