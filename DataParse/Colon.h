#pragma once
#include "Automatan.h"
class Colon :
	public Automatan
{
public:
	Colon();
	~Colon();
	virtual int read(FileReader& file);
	virtual std::string getName();
private:
	int colon(FileReader& file);
};

