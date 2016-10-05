#pragma once
#include "Automatan.h"
class Right_paren :
	public Automatan
{
public:
	Right_paren();
	~Right_paren();
	virtual int read(FileReader& file);
	virtual std::string getName();
};

