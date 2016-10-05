#pragma once
#include <string>
#include <vector>
class FileReader
{
public:
	FileReader();
	~FileReader();
	void read(std::string fileName);
	char getChar();
	std::string getString(int size);
	void reset();
	bool isEmpty();
	void test(std::string testFile);
	void removeString(int size);
	int lineNumber();
	void increaseLine();
private:
	std::string file;
	int p = 0;
	int line = 1;
};

