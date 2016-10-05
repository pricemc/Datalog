#pragma once
#include "Automatan.h"
class Undefined_String :
	public Automatan
{
public:
	Undefined_String();
	~Undefined_String();
	virtual int read(FileReader& file);
	virtual std::string getName();
private:
	bool first(FileReader& file);
	int afterFirst(FileReader& file);
	int apostrophe(FileReader& file);
};

