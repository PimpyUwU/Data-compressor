#include <iostream>
using namespace std;
#include "HuffmanEncoding.h"
#include "ShenonFanoencoding.h"
#include "LZWEncoding.h"

#define NEW_EXT "tjz"

char* newExtension(char* name);
char* scanName();
double coofecientOfCompression(char* name, char* newName);
bool checkDecodedFileForArtefacts(char* sourceFile, char* decodedFile);


int main()
{
	system("chcp 1251");
	system("cls");
	
	while (true) {
		cout << "1. Encode" << endl;
		cout << "2. Decode" << endl;
		cout << "3. Check for artefacts" << endl;
		cout << "4. Exit" << endl;

		int choice;
		cin >> choice;
		system("cls");
		switch (choice) {
			case 1: {
				cout << "1. Huffman" << endl;
				cout << "2. Shenon-Fano" << endl;
				cout << "3. LZW" << endl;
				int choice;
				cin >> choice;
				system("cls");
				char* name = scanName();
				switch (choice) {
				case 1: {
					HuffmanEncoding huff(name);
					huff.encode(newExtension(name));
					cout << "Coofecient of compression: " << coofecientOfCompression(name, newExtension(name)) << endl;
					break;
				}
				case 2: {
					ShenonFanoEncoding shenon(name);
					shenon.encode(newExtension(name));
					cout << "Coofecient of compression: " << coofecientOfCompression(name, newExtension(name)) << endl;
					break;
				}
				case 3: {
					LZWEncoding lzw(name);
					lzw.encode(newExtension(name));
					cout << "Coofecient of compression: " << coofecientOfCompression(name, newExtension(name)) << endl;
					break;
				}
				default:
					break;
				}
				system("pause");
				system("cls");
				break;
			}
			
			case 2: {
				cout << "1. Huffman" << endl;
				cout << "2. Shenon-Fano" << endl;
				cout << "3. LZW" << endl;
				int choice;
				cin >> choice;
				system("cls");
				char* FromFilename = scanName();
				char* ToFilename = scanName();
				switch (choice) {
				case 1: {
					HuffmanEncoding huff(FromFilename);
					huff.decode(FromFilename, ToFilename);
					break;
				}
				case 2: {
					ShenonFanoEncoding shenon(FromFilename);
					shenon.decode(FromFilename, ToFilename);
					break;
				}
				case 3: {
					LZWEncoding lzw(FromFilename);
					lzw.decode(FromFilename, ToFilename);
					break;
				}
				default:
					break;
				}
				system("cls");
				break;
			}

			case 3: {
				char* sourceFile = scanName();
				char* decodedFile = scanName();

				if (checkDecodedFileForArtefacts(sourceFile, decodedFile)) {
					cout << "File has artefacts" << endl;
				}
				else {
					cout << "File has no artefacts" << endl;
				}

				system("pause");
				system("cls");
				break;
			}

			case 4: {
				exit(0);
			}
		}
	}
}


char* scanName() {
	char* name = new char[200];
	cout << "Enter full filepath: ";
	cin >> name;
	return name;
}

char* newExtension(char* name) {
	char* newName = new char[100];
	const char* ext = NEW_EXT;
	int i = 0;
	while (name[i] != '.') {
		newName[i] = name[i];
		i++;
	}
	newName[i] = '.';
	i++;
	int j = 0;
	while (ext[j] != '\0') {
		newName[i] = ext[j];
		i++;
		j++;
	}
	newName[i] = '\0';
	return newName;
}

double coofecientOfCompression(char* name, char* newName) {
	FILE* f1 = fopen(name, "rb");
	FILE* f2 = fopen(newName, "rb");
	fseek(f1, 0, SEEK_END);
	fseek(f2, 0, SEEK_END);
	double size1 = ftell(f1);
	double size2 = ftell(f2);
	return size1 / size2;
}

#include <stdio.h>
#include <stdbool.h>

bool checkDecodedFileForArtefacts(char* sourceFile, char* decodedFile) {
	FILE* srcFile = fopen(sourceFile, "r");
	FILE* decFile = fopen(decodedFile, "r");

	if (srcFile == NULL || decFile == NULL) {
		printf("Не вдалося відкрити один або обидва файли.\n");
		return false;
	}

	// Порівнюємо файли
	char srcChar, decChar;
	while ((srcChar = fgetc(srcFile)) != EOF && (decChar = fgetc(decFile)) != EOF) {
		if (srcChar != decChar) {
			// Якщо символи не співпадають, то це артефакт
			fclose(srcFile);
			fclose(decFile);
			return true;
		}
	}

	fclose(srcFile);
	fclose(decFile);

	return false;
}
