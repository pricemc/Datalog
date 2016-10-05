#pragma once
#include "Automatan.h"
class Id :
	public Automatan
{
public:
	Id();
	~Id();
	virtual int read(FileReader& file);
	virtual std::string getName();
private:
	bool first(FileReader& file);
	int afterFirst(FileReader& file);
};

