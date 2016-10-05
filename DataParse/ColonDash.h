#pragma once
#include "Automatan.h"
class ColonDash :
	public Automatan
{
public:
	ColonDash();
	~ColonDash();
	virtual int read(FileReader& file);
	virtual std::string getName();
};

