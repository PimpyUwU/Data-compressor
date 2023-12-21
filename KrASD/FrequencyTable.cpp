#include "FrequencyTable.h"
#include <fstream>
using namespace std;

FrequencyTable::FrequencyTable()
{
	for (int i = 0; i < 256; i++)
	{
		frequencyTableArray[i] = 0;
	}
}

unsigned int* FrequencyTable::getTable()
{
	return frequencyTableArray;
}

void FrequencyTable::generateTable(char* filename)
{
	ifstream file(filename, std::ios::binary);
	char c;

	while (file.get(c))
	{
		frequencyTableArray[(unsigned char)c]++;
	}
	file.close();
}

void FrequencyTable::setTable(unsigned int* table)
{
	for (int i = 0; i < 256; i++)
	{
		frequencyTableArray[i] = *(table + i);
	}
}

FrequencyTable::FrequencyTable(unsigned int* table)
{
	setTable(table);
}