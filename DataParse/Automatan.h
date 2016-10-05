#pragma once
#include "FileReader.h"
#include <string>
class Automatan
{
public:
	Automatan(){};
	~Automatan(){};
	virtual int read(FileReader& file) = 0;
	virtual std::string getName() = 0;
};