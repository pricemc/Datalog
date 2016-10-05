#pragma once
#include "Automatan.h"
class Comma: public Automatan
{
public:
	Comma();
	~Comma();
	virtual int read(FileReader& file);
	virtual std::string getName();
};

