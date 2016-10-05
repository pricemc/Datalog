#include "Scanner.h"
#include <iostream>

Scanner::Scanner()
{
}


Scanner::~Scanner()
{
}

/*
generateToken
pre: automatan exists, input is not empty, size != 0
post: token
*/
Token* Scanner::generateToken(Automatan* a, FileReader input, int size)
{
	Token* output = new Token(a->getName(), input.getString(size), input.lineNumber());
	return output;
}

std::deque<Token*> Scanner::read(FileReader input)
{
	
	//Automata vector to run through in algorithm
	std::vector<Automatan*> automata = {
		new Comma(),
		new Period(),
		new Q_mark(),
		new Left_paren(),
		new Right_paren(),
		new Colon(),
		new ColonDash(),
		new Multiply(),
		new Add(),
		new Schemes(),
		new Facts(),
		new Rules(),
		new Queries(),
		new Id(),
		new String(),
		new Comment(),
		new Undefined_String(),
		new Undefined_Comment()
	};
	//Undefined Automata
	Undefined* undf = new Undefined();

	//output
	std::deque<Token*> output;

	//Main Algorithm
	while (!input.isEmpty())
	{
		int sl = 0;
		int automataHigh = -1;
		for (int i = 0; i < automata.size(); i++)	//find correct automata
		{
			int automataRead = automata[i]->read(input);
			if (automataRead > sl)
			{
				sl = automataRead;
				automataHigh = i;
			}
		}
		if (sl == 0)	//remove undefined and generate token
		{
			input.reset();
			char testt = input.getChar();
			if (!isspace(testt))
				output.push_back(generateToken(undf, input, 1));
			input.removeString(1);
		}
		else	//remove and generate token for longest automata
		{
			output.push_back(generateToken(automata[automataHigh], input, sl));
			input.removeString(sl);
		}
	}

	//generate EOF token
	output.push_back(new Token("EOF", "", input.lineNumber()));
	

	//mem clean
	delete undf;
	for (int i = 0; i < automata.size(); i++) delete automata[i];
	return output;
}

