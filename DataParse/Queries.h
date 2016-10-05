#pragma once
#include "Automatan.h"
class Queries :
	public Automatan
{
public:
	Queries();
	~Queries();
	virtual int read(FileReader& file);
	virtual std::string getName();
private:
	bool q(FileReader& file);
	bool u(FileReader& file);
	bool e(FileReader& file);
	bool r(FileReader& file);
	bool i(FileReader& file);
	bool es(FileReader& file);
	bool s(FileReader& file);
};

