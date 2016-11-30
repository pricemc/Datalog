#pragma once
#include "parameter.h"
class expression :
	public parameter
{
public:
	expression(parameter* head, parameter* op, parameter* tail);
	~expression();
	std::string toString();
	int type();
private:
	parameter* head;
	parameter* tail;
	parameter* op;
};

