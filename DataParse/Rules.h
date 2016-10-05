#pragma once
#include "Automatan.h"
class Rules :
	public Automatan
{
public:
	Rules();
	~Rules();
	virtual int read(FileReader& file);
	virtual std::string getName();
private:
	bool r(FileReader& file);
	bool u(FileReader& file);
	bool l(FileReader& file);
	bool e(FileReader& file);
	bool s(FileReader& file);
};

