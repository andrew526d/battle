#ifndef CONST_H
#define CONST_H
// --------------- ��������� � ������� ---------

#define FIELD_SIZE 10	//������ ����

enum cell_val			//��������� �������� ������
{
	CELL_EMPTY,
	CELL_WOUND,
	CELL_KILL,
	CELL_UNKNOWN
};

enum direction			//����������� ������� (������������ ��� ��������������)
{
	DIR_HOR,
	DIR_VER
};	
 
enum game_st			//������ ����
{
	GAME_UNKNOWN,
	GAME_WIN,
	GAME_LOOSE
};

#endif		
