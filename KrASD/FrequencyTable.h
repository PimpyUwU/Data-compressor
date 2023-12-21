#pragma once
class FrequencyTable
{
public:
	FrequencyTable();
	FrequencyTable(unsigned int* table);
	void generateTable(char* filename);
	unsigned int* getTable();
	void setTable(unsigned int* table);
private:
	unsigned int frequencyTableArray[256];
};


