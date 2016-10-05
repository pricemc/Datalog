#pragma once
#include "Automatan.h"
class Left_paren :
	public Automatan
{
public:
	Left_paren();
	~Left_paren();
	virtual int read(FileReader& file);
	virtual std::string getName();
};

