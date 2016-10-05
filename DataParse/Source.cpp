#include <iostream>
#include <vector>
#include <deque>
#include "Scanner.h"
#include "FileReader.h"
#include "Token.h"

#include "Parser.h"



int main(int argc, char *argv[])
{
	//Usage Requirements
	FileReader input;
	std::string test = "Schemes#|block|#:";
	if (argc != 2)
	{
		//use test data
		//std::cout << "usage: " << argv[0] << " <filename>\n";
		//std::cout << "Using test data instead: \n" << test << std::endl;
		input.test(test);
	}
	else {
		input.read(argv[1]);
	}
	Scanner a;
	std::deque<Token*> tokens = a.read(input);

	//for (int i = 0; i < tokens.size(); i++)
	//	std::cout << tokens[i]->toString() << std::endl;
	Parser* parser = new Parser();
	std::cout << (parser->parse(tokens) ? "Success!" : "Failure.\n" + tokens.front()->toString());
	std::cout << std::endl;
	for (int i = 0; i < tokens.size(); i++) delete tokens[i];
	delete parser;
	system("pause");
	return 0;
}