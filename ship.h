#ifndef SHIP_H
#define SHIP_H


class ship
{

private:
	int x;		//���������� x
	int y;		//���������� y
	int len;	//����� �������
	enum dir	//����������� (������������ ��� ��������������)
	{
		hor,
		ver
	};
};


#endif