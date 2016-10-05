#pragma once
#include "Automatan.h"
class Schemes :
	public Automatan
{
public:
	Schemes();
	~Schemes();
	virtual int read(FileReader& file);
	virtual std::string getName();
private:
	bool s(FileReader& file);
	bool c(FileReader& file);
	bool h(FileReader& file);
	bool e(FileReader& file);
	bool m(FileReader& file);
	bool es(FileReader& file);
	bool ss(FileReader& file);
};

