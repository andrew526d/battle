#include <iostream>
#include <vector>
#include "enumerator.h"
#include "ship.h"
#include "field.h"

using std::cout;
using std::vector;
using std::reference_wrapper;

void test_print();
int main() 
{

	
	try
	{
		test_print();
	}
	
	catch(Error err)
	{
		cout << "Сбой в программе: " << err.err_txt << endl;
	}

}

void test_print()
{
	Field f1;
	Cell c1;
	int i;
	vector<reference_wrapper<Field>> fields;

	fields.push_back(f1);
	fields.push_back(f1);
	fields.push_back(f1);
		
	for(i = CELL_MIN + 1 ; i<CELL_MAX; i++)
	{
		c1.set_x(i);
		c1.set_y(0);
		c1.set_val((cell_val)i);
		f1.set_cell(c1);
	}
		
	print(fields);
}