#include "HuffmanEncoding.h"
#include <fstream>

HuffmanEncoding::HuffmanEncoding(char* filename)
{
    this->filename = filename;
    this->tree = new HuffmanTree(filename);
}

void HuffmanEncoding::encode(char* toFileName)
{
    std::ifstream file(this->filename, std::ios::binary);
    std::ofstream toFile(toFileName, std::ios::binary);

    unsigned char byte = 0;
    int bitPos = 1;
    std::string buffer;

    unsigned int* frequencies = this->tree->getHeap().getFrequencies();
    toFile.write((const char*)frequencies, sizeof(unsigned int) * 256);

    char inChar = 0;
    while (file.read(&inChar, sizeof(unsigned char)))
    {
        buffer = tree->getTable()->getCode(inChar);
        for (int i = 0; i < buffer.length(); i++)
        {
            if (buffer[i] == '1')
            {
                byte = byte | (1 << (8 - bitPos));
            }
            bitPos++;
            if (bitPos > 8)
            {
                toFile.write((char*)(&byte), sizeof(unsigned char));
                byte = 0;
                bitPos = 1;
            }
        }
    }
    if (bitPos != 1)
    {
        toFile.write((char*)(&byte), sizeof(unsigned char));
    }

    toFile.close();
    file.close();
}


void HuffmanEncoding::decode(char* fromFile, char* toFileName)
{
    std::ifstream file(fromFile, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Unable to open file: " << fromFile << "\n";
        return;
    }

    std::ofstream toFile(toFileName, std::ios::binary);
    if (!toFile.is_open()) {
        std::cout << "Unable to open file: " << toFileName << "\n";
        file.close();
        return;
    }

    unsigned int* frequencies = new unsigned int[256];
    file.read(reinterpret_cast<char*>(frequencies), sizeof(unsigned int) * 256);
    this->tree = new HuffmanTree(frequencies);

    Node* node = this->tree->getTreeRoot();
    unsigned char inChar = 0;
    unsigned char outChar = 0;

    while (file.read(reinterpret_cast<char*>(&inChar), sizeof(unsigned char)))
    {
        for (int i = 0; i < 8; i++)
        {
            if (inChar & (1 << (7 - i)))
            {
                node = node->getRight();
            }
            else
            {
                node = node->getLeft();
            }
            if (node->getLeft() == NULL && node->getRight() == NULL)
            {
                outChar = node->getLetter()->getCode();
                toFile.write(reinterpret_cast<char*>(&outChar), sizeof(unsigned char));
                node = this->tree->getTreeRoot(); // Reset the node to the root of the Huffman tree
            }
        }
    }

    delete[] frequencies; // free the allocated memory

    toFile.close();
    file.close();
}

