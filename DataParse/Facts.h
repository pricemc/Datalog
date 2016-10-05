#pragma once
#include "Automatan.h"
class Facts :
	public Automatan
{
public:
	Facts();
	~Facts();
	virtual int read(FileReader& file);
	virtual std::string getName();
private:
	int s(FileReader& file);
	int t(FileReader& file);
	int c(FileReader& file);
	int a(FileReader& file);
	int f(FileReader& file);
};

