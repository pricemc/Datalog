#include "expression.h"


expression::expression(parameter* head_in, parameter* op_in, parameter* tail_in)
{
	head = head_in;
	op = op_in;
	tail = tail_in;
}


expression::~expression()
{
}


std::string expression::toString()
{
	return "(" + head->toString() + "," +  op->toString() + "," + tail->toString() + ")";
}

int expression::type()
{
	return 2;
}