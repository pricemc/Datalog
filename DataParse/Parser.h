#pragma once
#include <iostream>
#include <deque>

#include "Token.h"

class Parser
{
public:
	Parser();
	~Parser();
	bool parse(std::deque<Token*>& tokens);
private:
	bool datalogProgram(std::deque<Token*>& tokens);
	bool scheme(std::deque<Token*>& tokens);
	bool schemeList(std::deque<Token*>& tokens);
	bool idList(std::deque<Token*>& tokens);
	bool fact(std::deque<Token*>& tokens);
	bool factList(std::deque<Token*>& tokens);
	bool rule(std::deque<Token*>& tokens);
	bool ruleList(std::deque<Token*>& tokens);
	bool headPredicate(std::deque<Token*>& tokens);
	bool predicate(std::deque<Token*>& tokens);
	bool predicateList(std::deque<Token*>& tokens);
	bool parameter(std::deque<Token*>& tokens);
	bool parameterList(std::deque<Token*>& tokens);
	bool expression(std::deque<Token*>& tokens);
	bool moperator(std::deque<Token*>& tokens);
	bool query(std::deque<Token*>& tokens);
	bool queryList(std::deque<Token*>& tokens);
	bool stringList(std::deque<Token*>& tokens);

	bool COMMA(std::deque<Token*>& tokens);
	bool PERIOD(std::deque<Token*>& tokens);
	bool Q_MARK(std::deque<Token*>& tokens);
	bool LEFT_PAREN(std::deque<Token*>& tokens);
	bool RIGHT_PAREN(std::deque<Token*>& tokens);
	bool COLON(std::deque<Token*>& tokens);
	bool COLON_DASH(std::deque<Token*>& tokens);
	bool MULTIPLY(std::deque<Token*>& tokens);
	bool ADD(std::deque<Token*>& tokens);
	bool SCHEMES(std::deque<Token*>& tokens);
	bool FACTS(std::deque<Token*>& tokens);
	bool RULES(std::deque<Token*>& tokens);
	bool QUERIES(std::deque<Token*>& tokens);
	bool ID(std::deque<Token*>& tokens);
	bool STRING(std::deque<Token*>& tokens);
	bool COMMENT(std::deque<Token*>& tokens);
	bool mEOF(std::deque<Token*>& tokens);

	bool restart(std::deque<Token*>& tokens);
};

