#pragma once
#include "Automatan.h"
class Add :
	public Automatan
{
public:
	Add();
	~Add();
	virtual int read(FileReader& file);
	virtual std::string getName();
};

