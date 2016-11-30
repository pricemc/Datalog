#include "parameter.h"


parameter::parameter(std::string name_in)
{
	name = name_in;
}
parameter::parameter()
{
}


parameter::~parameter()
{
}

std::string parameter::toString()
{
	return name;
}

int parameter::type()
{
	if (name.substr(0, 1) == "\'") return 0;
	return 1;
}