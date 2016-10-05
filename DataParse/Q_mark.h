#pragma once
#include "Automatan.h"
class Q_mark :
	public Automatan
{
public:
	Q_mark();
	~Q_mark();
	virtual int read(FileReader& file);
	virtual std::string getName();
};

