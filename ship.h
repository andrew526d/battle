#ifndef SHIP_H
#define SHIP_H


class ship
{

private:
	int x;		//координата x
	int y;		//координата y
	int len;	//длина корабля
	enum dir	//направление (вертикальное или горизонтальное)
	{
		hor,
		ver
	};
};


#endif