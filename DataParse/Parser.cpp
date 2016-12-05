#include "Parser.h"
#include <algorithm>

Parser::Parser()
{
}


Parser::~Parser()
{
}


std::pair<bool,datalogProgram> Parser::parse(std::deque<Token*>& tokens)
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
		keepGoing = mdatalogProgram(tokens);
	}
	std::pair<bool, datalogProgram> output = std::make_pair(keepGoing, program);
	return output;
}

bool Parser::mdatalogProgram(std::deque<Token*>& tokens)
{
	bool output = datalogSchemes(tokens) && datalogFacts(tokens) 
		&& datalogRules(tokens) && datalogQueries(tokens);
	if (output)
	{
		for (int i = 0; i < program.facts.size(); i++)
		{
			for (int j = 0; j < program.facts[i]->params.size(); j++)
			{
				bool yes = true;
				for (std::set<parameter*>::iterator x = program.domain.begin(); x != program.domain.end(); x++)
				{
					parameter* element = *x;
					if (program.facts[i]->params[j]->name == element->name) yes = false;
				}
				if (yes) program.addDomain(program.facts[i]->params[j]);
			}
		}
	}
	return output;
}
bool Parser::datalogSchemes(std::deque<Token*>& tokens)
{
	return (SCHEMES(tokens) && COLON(tokens) && scheme(tokens) && schemeList(tokens));
}
bool Parser::datalogFacts(std::deque<Token*>& tokens)
{
	return (FACTS(tokens) && COLON(tokens) && factList(tokens));
}
bool Parser::datalogRules(std::deque<Token*>& tokens)
{
	return (RULES(tokens) && COLON(tokens) && ruleList(tokens));
}
bool Parser::datalogQueries(std::deque<Token*>& tokens)
{
	return (QUERIES(tokens) && COLON(tokens) && query(tokens) && queryList(tokens));
}

bool Parser::scheme(std::deque<Token*>& tokens)
{
	bool output = false;
	std::pair<bool, std::deque<parameter*>> oidList;
	std::string first = tokens.front()->getString();
	std::string second = tokens[2]->getString();
	if (ID(tokens))
	{
		output = (LEFT_PAREN(tokens) && ID(tokens));
		oidList = idList(tokens);
		output = output && oidList.first && RIGHT_PAREN(tokens);
		oidList.second.push_front(new parameter(second));
	}
	std::deque<parameter*> a = oidList.second;
	if (output)
	{
		predicate* b = new predicate(parameter(first), a);
		program.addScheme(b);
	}
	return output;

}
bool Parser::schemeList(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "ID")
		return (scheme(tokens) && schemeList(tokens));
	else if (mEOF(tokens) || restart(tokens))
		return true;
	return false;
}
std::pair<bool, std::deque<parameter*>> Parser::idList(std::deque<Token*>& tokens)
{
	std::pair<bool,std::deque < parameter* >> output;
	
	if (COMMA(tokens))
	{
		std::string first = tokens.front()->getString();
		if (ID(tokens))
		{
			std::pair<bool, std::deque<parameter*>> output = idList(tokens);
			output.second.push_front(new parameter(first));
			return std::make_pair(true, output.second);
		}
	}
	else if (tokens.front()->getName() == "RIGHT_PAREN")
		return std::make_pair(true, output.second);
	output.first = false;
	return output;
}
bool Parser::fact(std::deque<Token*>& tokens)
{
	/*if (ID(tokens))
		return (LEFT_PAREN(tokens) && STRING(tokens)
			&& stringList(tokens) && RIGHT_PAREN(tokens) && PERIOD(tokens));
	return false;*/

	bool output = false;
	std::pair<bool, std::deque<parameter*>> oidList;
	std::string first = tokens.front()->getString();
	std::string second = tokens[2]->getString();
	if (ID(tokens))
	{
		output = (LEFT_PAREN(tokens) && STRING(tokens));
		oidList = stringList(tokens);
		output = output && oidList.first && RIGHT_PAREN(tokens) && PERIOD(tokens);
		oidList.second.push_front(new parameter(second));
	}
	std::deque<parameter*> a = oidList.second;
	if (output)
	{
		predicate* b = new predicate(parameter(first), a);
		program.addFact(b);
	}
	return output;
}
bool Parser::factList(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "ID")
		return (fact(tokens) && factList(tokens));
	else if (mEOF(tokens) || restart(tokens))
		return true;
	return false;
}
bool Parser::mrule(std::deque<Token*>& tokens)
{ 
	std::pair<bool, predicate*> head = headPredicate(tokens);
	std::deque<predicate*> output;
	std::pair<bool, std::deque<predicate*>> list;
	list.first = false;
	std::pair<bool, predicate*> rules;
	rules.first = false;
	bool last = false;
	if (head.first)
	{
		if (COLON_DASH(tokens))
		{
			rules = mpredicate(tokens);
			if (rules.first) list = predicateList(tokens);
			if (list.first) last = PERIOD(tokens);
		}
	}
	if (last)
	{
		output = list.second;
		output.push_front(rules.second);
		program.addRule(new rule(head.second, output));
		return true;
	}
	return false;

}
bool Parser::ruleList(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "ID")
		return (mrule(tokens) && ruleList(tokens));
	else if (mEOF(tokens) || restart(tokens))
		return true;
	return false;
}
std::pair<bool, predicate*> Parser::headPredicate(std::deque<Token*>& tokens)
{
	bool output = true;
	std::pair<bool, std::deque<parameter*>> oidList;
	std::string first = tokens.front()->getString();
	std::string second = tokens[2]->getString();
	predicate* p_output = NULL;
	if (ID(tokens))
	{
		output = (LEFT_PAREN(tokens) && ID(tokens));
		oidList = idList(tokens);
		output = output && oidList.first && RIGHT_PAREN(tokens);
		oidList.second.push_front(new parameter(second));
	}
	std::deque<parameter*> a = oidList.second;
	if (output)
	{
		p_output = new predicate(parameter(first), a);
	}
	return std::make_pair(output, p_output);
}
std::pair<bool, predicate*> Parser::mpredicate(std::deque<Token*>& tokens)
{
	bool output = true;
	std::pair<bool, std::deque<parameter*>> oidList;
	std::string first = tokens.front()->getString();
	std::string second = tokens[2]->getString();
	predicate* p_output = NULL;
	if (ID(tokens))
	{
		output = (LEFT_PAREN(tokens) && mparameter(tokens).first);
		oidList = parameterList(tokens);
		output = output && oidList.first && RIGHT_PAREN(tokens);
		oidList.second.push_front(new parameter(second));
	}
	std::deque<parameter*> a = oidList.second;
	if (output)
	{
		p_output = new predicate(parameter(first), a);
	}
	return std::make_pair(output, p_output);
}
std::pair<bool, std::deque<predicate*>> Parser::predicateList(std::deque<Token*>& tokens)
{
	bool output = true;
	std::deque<predicate*> p_output;
	if (COMMA(tokens))
	{
		std::pair<bool, predicate*> first = mpredicate(tokens);
		std::pair<bool, std::deque<predicate*>> list = predicateList(tokens);
		output = output && first.first && list.first;
		list.second.push_front(first.second);
		list.first = output;
		return list;
	}
	if (tokens.front()->getName() == "PERIOD") return std::make_pair(true, p_output);
	return std::make_pair(false, p_output);
}
std::pair<bool, parameter*> Parser::mparameter(std::deque<Token*>& tokens)
{
	std::string a = tokens.front()->getString();
	if (ID(tokens) || STRING(tokens)) return std::make_pair(true, new parameter(a));
	return mexpression(tokens);
}
std::pair<bool, std::deque<parameter*>> Parser::parameterList(std::deque<Token*>& tokens)
{
	bool output = true;
	std::deque<parameter*> p_output;
	if (COMMA(tokens))
	{
		std::pair<bool, parameter*> first = mparameter(tokens);
		std::pair<bool, std::deque<parameter*>> list = parameterList(tokens);
		output = output && first.first && list.first;
		list.second.push_front(first.second);
		list.first = output;
		return list;
	}
	else if (tokens.front()->getName() == "RIGHT_PAREN")
		return std::make_pair(true, p_output);
	return std::make_pair(false, p_output);
}
std::pair<bool, expression*> Parser::mexpression(std::deque<Token*>& tokens)
{
	bool output = true;
	output = output && LEFT_PAREN(tokens);
	std::pair<bool, parameter*> first = mparameter(tokens);
	std::pair<bool, parameter*> second = moperator(tokens);
	std::pair<bool, parameter*> third = mparameter(tokens);
	output = output && first.first && second.first && third.first && RIGHT_PAREN(tokens);
	return std::make_pair(output, new expression(first.second, second.second, third.second));
}
std::pair<bool, parameter*> Parser::moperator(std::deque<Token*>& tokens)
{
	std::string first = tokens.front()->getString();
	if (MULTIPLY(tokens) || ADD(tokens)) return std::make_pair(true, new parameter(first));
}
bool Parser::query(std::deque<Token*>& tokens)
{
	std::pair<bool, predicate*> p = mpredicate(tokens);
	if (p.first && Q_MARK(tokens))
	{
		program.addQueries(p.second);
		return true;
	}
	return false;
}
bool Parser::queryList(std::deque<Token*>& tokens)
{
	if (tokens.front()->getName() == "ID")
		return query(tokens) && queryList(tokens);
	else if (mEOF(tokens) || restart(tokens))
		return true;
	return false;
}
std::pair<bool, std::deque<parameter*>> Parser::stringList(std::deque<Token*>& tokens)
{
	/*if (COMMA(tokens))
		return (STRING(tokens) && stringList(tokens));
	else if (tokens.front()->getName() == "RIGHT_PAREN")
		return true;
	return false;*/

	bool output = true;
	std::deque<parameter*> p_output;
	if (COMMA(tokens))
	{
		std::string first = tokens.front()->getString();
		output = output && STRING(tokens);
		std::pair<bool, std::deque<parameter*>> list = stringList(tokens);
		output = output && list.first;
		list.second.push_front(new parameter(first));
		list.first = output;
		return list;
	}
	else if (tokens.front()->getName() == "RIGHT_PAREN")
		return std::make_pair(true, p_output);
	return std::make_pair(false, p_output);
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