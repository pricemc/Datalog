#include "FileReader.h"
#include <fstream>
#include <iostream>

/*
Read
	reads file into string for later consumption
	pre: fileName is not empty string
	post: file is occuied by contents of fileName
*/
void FileReader::read(std::string fileName)
{
	std::ifstream myfile(fileName);
	std::string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			file += line + "\n";
		}
		myfile.close();
	}
	else std::cout << "Unable to open file\n";
}

FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}

bool FileReader::isEmpty()
{
	if (file.length() == 0) return true;
	return false;
}
void FileReader::reset()
{
	p = 0;
}

char FileReader::getChar()
{
	if (p >= file.length()) return EOF;
	char a = file.at(p);
	p++;
	return a;
}

std::string FileReader::getString(int size)
{
	return file.substr(0, size);
}

void FileReader::removeString(int size)
{
	reset();
	for (int i = 0; i < size; i++)
		if (getChar() == '\n')
			line++;
	file.erase(0, size);
}

int FileReader::lineNumber()
{
	return line;
}

//set file string to test contents
void FileReader::test(std::string testFile)
{
	file = testFile;
}

void FileReader::increaseLine()
{
	line++;
}