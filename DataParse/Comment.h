#pragma once
#include "Automatan.h"
class Comment :
	public Automatan
{
public:
	Comment();
	~Comment();
	virtual int read(FileReader& file);
	virtual std::string getName();
private:
	bool hash(FileReader& file);
	int whichComment(FileReader& file);
	int line(FileReader& file);
	int block(FileReader& file);
};

