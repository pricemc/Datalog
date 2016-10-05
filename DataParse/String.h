#pragma once
#include "Automatan.h"
class String :
	public Automatan
{
public:
	String();
	~String();
	virtual int read(FileReader& file);
	virtual std::string getName();
private:
	bool first(FileReader& file);
	int afterFirst(FileReader& file);
	int apostrophe(FileReader& file);
};

