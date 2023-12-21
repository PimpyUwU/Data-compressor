#include "ShenonFanoEncoding.h"
#include <fstream>

ShenonFanoEncoding::ShenonFanoEncoding(char* filename){
	this->filename = filename;
	this->sf = new ShenonFanoAlgorithm(filename);
}

void ShenonFanoEncoding::encode(char* toFileName)
{
    std::ifstream file(this->filename, std::ios::binary);
    std::ofstream toFile(toFileName, std::ios::binary);

    unsigned char byte = 0;
    int bitPos = 0; // Start from 0
    std::string buffer;

    unsigned int* frequencies = this->sf->getFrequencies();
    // Write each frequency individually
    for (int i = 0; i < 256; i++)
    {
        toFile.write((char*)&frequencies[i], sizeof(unsigned int));
    }

    char inChar = 0;
    while (file.read(&inChar, sizeof(unsigned char)))
    {
        buffer = sf->getCodesTable()->getCode(inChar);
        for (int i = 0; i < buffer.length(); i++)
        {
            if (buffer[i] == '1')
            {
                byte = byte | (1 << (7 - bitPos)); // Shift from least significant bit
            }
            bitPos++;
            if (bitPos > 7) // Write the byte when it's full
            {
                toFile.write((char*)(&byte), sizeof(unsigned char));
                byte = 0;
                bitPos = 0;
            }
        }
    }
    // Write the last byte even if it's not full
    if (bitPos != 0)
    {
        toFile.write((char*)(&byte), sizeof(unsigned char));
    }

    toFile.close();
    file.close();
}


void ShenonFanoEncoding::decode(char* fromFileName, char* toFileName)
{
    std::ifstream file(fromFileName, std::ios::binary);
    std::ofstream toFile(toFileName, std::ios::binary);

    unsigned int* frequencies = new unsigned int[256];
    file.read(reinterpret_cast<char*>(frequencies), sizeof(unsigned int) * 256);

    this->sf = new ShenonFanoAlgorithm(frequencies);
    CodesTable* codesTable = this->sf->getCodesTable();

    unsigned char inChar = 0;
    unsigned char outChar = 0;
    std::string buffer;

    while (file.read(reinterpret_cast<char*>(&inChar), sizeof(unsigned char)))
    {
        for (int i = 0; i < 8; i++)
        {
            buffer += ((inChar >> (7 - i)) & 1) ? '1' : '0';
            if (codesTable->hasLetter(buffer))
            {
                outChar = codesTable->getChar(buffer);
                toFile.write(reinterpret_cast<char*>(&outChar), sizeof(unsigned char));
                buffer.clear();
            }
        }
    }

    delete[] frequencies; // free the allocated memory

    toFile.close();
    file.close();
}
