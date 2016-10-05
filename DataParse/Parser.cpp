#include "Parser.h"
#include <algorithm>

Parser::Parser()
{
}


Parser::~Parser()
{
}


bool Parser::parse(std::deque<Token*>& tokens)
{
	for (auto i = tokens.begin(); i != tokens.end(); /*NOTE: no incrementation of the iterator here*/) {
		if ((*i)->getName() == "COMMENT")
		{
			delete (*i);
			i = tokens.erase(i); // erase returns the next iterator
		}
		else
			++i; // otherwise increment it by yourself
	}
	bool keepGoing = true;
	while (tokens.size() > 0 && keepGoing)
	{
		keepGoing = datalogProgram(tokens);
	}
	return keepGoing;
}

bool Parser::datalogProgram(std::deque<Token*>& tokens)
{
	if (SCHEMES(tokens))
		return datalogSchemes(tokens);
	if (FACTS(tokens))
		return datalogFacts(tokens);
	if (RULES(tokens))
		return datalogRules(tokens);
	if (QUERIES(tokens))
		return datalogQueries(tokens);
	return false;
}
bool Parser::datalogSchemes(std::deque<Token*>& tokens)
{
	return (COLON(tokens) && scheme(tokens) && schemeList(tokens));
}
bool Parser::datalogFacts(std::deque<Token*>& tokens)
{
	return (COLON(tokens) && factList(tokens));
}
bool Parser::datalogRules(std::deque<Token*>& tokens)
{
	return (COLON(tokens) && ruleList(tokens));
}
bool Parser::datalogQueries(std::deque<Token*>& tokens)
{
	return (COLON(tokens) && query(tokens) && queryList(tokens));
}

bool Parser::scheme(std::deque<Token*>& tokens)
{
	if (ID(tokens))
		return (LEFT_PAREN(tokens) && ID(tokens) 
			&& idList(tokens) && RIGHT_PAREN(tokens));
}
bool Parser::schemeList(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "ID")
		return (scheme(tokens) && schemeList(tokens));
	else if (mEOF(tokens) || restart(tokens))
		return true;
	return false;
}
bool Parser::idList(std::deque<Token*>& tokens)
{
	if (COMMA(tokens))
		return (ID(tokens) && idList(tokens));
	else if (tokens.front()->getName() == "RIGHT_PAREN")
		return true;
	return false;
}
bool Parser::fact(std::deque<Token*>& tokens)
{
	if (ID(tokens))
		return (LEFT_PAREN(tokens) && STRING(tokens)
			&& stringList(tokens) && RIGHT_PAREN(tokens) && PERIOD(tokens));
	return false;
}
bool Parser::factList(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "ID")
		return (fact(tokens) && factList(tokens));
	else if (mEOF(tokens) || restart(tokens))
		return true;
	return false;
}
bool Parser::rule(std::deque<Token*>& tokens)
{ 
	if (headPredicate(tokens))
		return  COLON_DASH(tokens) && predicate(tokens) && predicateList(tokens) && PERIOD(tokens);
}
bool Parser::ruleList(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "ID")
		return (rule(tokens) && ruleList(tokens));
	else if (mEOF(tokens) || restart(tokens))
		return true;
	return false;
}
bool Parser::headPredicate(std::deque<Token*>& tokens)
{
	if (ID(tokens))
		return LEFT_PAREN(tokens) && ID(tokens) && idList(tokens) && RIGHT_PAREN(tokens);
	return false;
}
bool Parser::predicate(std::deque<Token*>& tokens)
{
	if (ID(tokens))
		return LEFT_PAREN(tokens) && parameter(tokens) && parameterList(tokens) && RIGHT_PAREN(tokens);
	return false;
}
bool Parser::predicateList(std::deque<Token*>& tokens)
{
	if(COMMA(tokens)) return predicate(tokens) && predicateList(tokens);
	if (tokens.front()->getName() == "PERIOD") return true;
	return false;
}
bool Parser::parameter(std::deque<Token*>& tokens)
{
	if (ID(tokens)) return true;
	if (STRING(tokens)) return true;
	return expression(tokens);
}
bool Parser::parameterList(std::deque<Token*>& tokens)
{
	if (COMMA(tokens))
		return parameter(tokens) && parameterList(tokens);
	else if (tokens.front()->getName() == "RIGHT_PAREN")
		return true;
	return false;
}
bool Parser::expression(std::deque<Token*>& tokens)
{
	return LEFT_PAREN(tokens) && parameter(tokens) && moperator(tokens) 
		&& parameter(tokens) && RIGHT_PAREN(tokens);
}
bool Parser::moperator(std::deque<Token*>& tokens)
{
	if (MULTIPLY(tokens)) return true;
	return ADD(tokens);
}
bool Parser::query(std::deque<Token*>& tokens)
{
	return predicate(tokens) && Q_MARK(tokens);
}
bool Parser::queryList(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "ID")
		return query(tokens) && queryList(tokens);
	else if (mEOF(tokens) || restart(tokens))
		return true;
	return false;
}
bool Parser::stringList(std::deque<Token*>& tokens)
{
	if (COMMA(tokens))
		return (STRING(tokens) && stringList(tokens));
	else if (tokens.front()->getName() == "RIGHT_PAREN")
		return true;
	return false;
}


bool Parser::COMMA(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "COMMA")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::PERIOD(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "PERIOD")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::Q_MARK(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "Q_MARK")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::LEFT_PAREN(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "LEFT_PAREN")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::RIGHT_PAREN(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "RIGHT_PAREN")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::COLON(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "COLON")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::COLON_DASH(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "COLON_DASH")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::MULTIPLY(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "MULTIPLY")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::ADD(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "ADD")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::SCHEMES(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "SCHEMES")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::FACTS(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "FACTS")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::RULES(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "RULES")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::QUERIES(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "QUERIES")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::ID(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "ID")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::STRING(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "STRING")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::COMMENT(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "COMMENT")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}
bool Parser::mEOF(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "EOF")
	{
		delete tokens.front();
		tokens.pop_front();
		return true;
	}
	return false;
}

bool Parser::restart(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "SCHEMES" ||
		tokens.front()->getName() == "FACTS" ||
		tokens.front()->getName() == "RULES" ||
		tokens.front()->getName() == "QUERIES")
		return true;
	return false;
}