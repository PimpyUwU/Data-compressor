#include <iostream>
#include "FreqencyTable.h"

int main()
{
	FreqencyTable table;
	table.generateTable("D:\\Code\\C C++\\Kursach ASD\\test.txt");
	int* tableArray = table.getTable();
	for (int i = 0; i < 256; i++)
	{
		cout << unsigned char(i) << " " << tableArray[i] << endl;
	}
	return 0;
}