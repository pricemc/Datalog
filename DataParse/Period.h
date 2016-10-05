#pragma once
#include "Automatan.h"
class Period :
	public Automatan
{
public:
	Period();
	~Period();
	virtual int read(FileReader& file);
	virtual std::string getName();
};

