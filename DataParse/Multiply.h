#pragma once
#include "Automatan.h"
class Multiply :
	public Automatan
{
public:
	Multiply();
	~Multiply();
	virtual int read(FileReader& file);
	virtual std::string getName();
};

