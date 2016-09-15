#include "player.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#define MAX_READ_BUF 100

using std::cout;
using std::endl;
using std::string;
using std::to_string;


Player_TCP::Player_TCP(int port_num)
{
	socklen_t addrlen;
	struct sockaddr_in server, client;
	int ret;
	
	port = port_num;
	
	srv_sock = socket(AF_INET, SOCK_STREAM, 0);	
	if (srv_sock == -1)
	{
		Error err;
		err.err_txt = "Ошибка в функции Player_TCP::Player_TCP. Невозможно открыть сокет";
		throw(err);
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);
	
	ret = bind(srv_sock,(struct sockaddr*)&server,sizeof(server));
	if (ret == -1)
	{
		Error err;
		err.err_txt = "Ошибка в функции Player_TCP::Player_TCP. Ошибка bind";
		throw(err);
	}
	
	ret = listen(srv_sock, 1);
	if (ret == -1)
	{
		Error err;
		err.err_txt = "Ошибка в функции Player_TCP::Player_TCP. Ошибка listen";
		throw(err);
	}
	
	addrlen = sizeof(client);
	cl_sock = accept(srv_sock, (struct sockaddr*)&client, &addrlen);
	if (cl_sock == -1)
	{
		Error err;
		err.err_txt = "Ошибка в функции Player_TCP::Player_TCP. Ошибка accept";
		throw(err);
	}

	close(srv_sock);
}

Player_TCP::~Player_TCP()
{
	close(cl_sock);
}

Cell Player_TCP::ask_cell()
{
	int len;
	char x,y;
	Cell cell;
	char str[MAX_READ_BUF];
	
	print("Ваш ход: ");

	while(1)
	{
		len = read(cl_sock, str, sizeof(str));

		if(len!=4)
		{
			print("Неверное значение\n");
			print("Ваш ход: ");
			continue;
		}

		x = str[0] - 'a';
		y = str[1] - '0';
		
		if(x < 0 || x > FIELD_SIZE || y < 0 || y > FIELD_SIZE)
		{
			print("Неверное значение\n");
			print("Ваш ход: ");
			continue;
		}
		else
		{
			cell.x = (int)x;
			cell.y = (int)y;
			return cell;
		}
		
	}
}

cell_val Player_TCP::ask_val(Cell cell) 
{
	int len;
	char str[MAX_READ_BUF];
	int val;
	
	string xstr(1,'a' + cell.x);
	string instr = "Введите результат (Мимо: " + to_string(CELL_EMPTY) + 
		", Ранил: " + to_string(CELL_WOUND) + 
		", Убил: " + to_string(CELL_KILL) + "): ";
	
	print("Противник сходил: " + xstr + to_string(cell.y) + "\n");
	print(instr);
	
	while(1)
	{
		len = read(cl_sock, str, sizeof(str));

		if(len!=3)
		{
			print("Неверное значение\n");
			print(instr);
			continue;
		}

		val = str[0] - '0';
		
		if(val != CELL_EMPTY && val != CELL_WOUND && val != CELL_KILL)
		{
			print("Неверное значение\n");
			print(instr);
		}
		else
			return (cell_val)val;

	};
}

void Player_TCP::send_val(cell_val val)
{	
	switch(val)
	{
		case CELL_EMPTY: print("Мимо\n"); break;
		case CELL_WOUND: print("Ранил\n"); break;
		case CELL_KILL: print("Убил\n"); break;
		default:
		{
			Error err;
			err.err_txt = "Ошибка в функции Player_TCP::send_val. Недопустимое значение val = " + to_string(val);
			throw(err);
		}
	}
}

void Player_TCP::bad_cell(Cell cell)
{

}
	
void Player_TCP::bad_val(Cell cell, cell_val val)
{
	print("Неверное значение\n");
}
	
void Player_TCP::win()
{
	print("Вы выиграли!\n");
}
	
void Player_TCP::lose()
{
	print("Вы проиграли!\n");
}

void Player_TCP::print(string msg)
{
	write(cl_sock, msg.c_str(), msg.size());
}