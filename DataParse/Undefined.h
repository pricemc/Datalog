#pragma once
#include "Automatan.h"
class Undefined :
	public Automatan
{
public:
	Undefined();
	~Undefined();
	virtual int read(FileReader& file);
	virtual std::string getName();
};

