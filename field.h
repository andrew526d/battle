#ifndef FIELD_H
#define FIELD_H 

#include <iostream>
#include "const.h"

using std::ostream;
using std::cout;
using std::endl;

class Field
{
public:
	bool is_end();

private:
	int buf[FIELD_SIZE][FIELD_SIZE];

};

class FieldShips : Field
{
	
};

class FieldEmpty : Field
{
	
};



#endif