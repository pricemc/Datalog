#pragma once
#include "Automatan.h"
class Undefined_Comment :
	public Automatan
{
public:
	Undefined_Comment();
	~Undefined_Comment();
	virtual int read(FileReader& file);
	virtual std::string getName();
private:
	bool hash(FileReader& file);
	int whichComment(FileReader& file);
	int block(FileReader& file);
};

