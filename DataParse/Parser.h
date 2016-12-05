#pragma once
#include <iostream>
#include <deque>
#include <utility>

#include "Token.h"
#include "datalogProgram.h"
#include "expression.h"
#include "parameter.h"
#include "predicate.h"
#include "rule.h"

class Parser
{
public:
	Parser();
	~Parser();
	std::pair<bool,datalogProgram> parse(std::deque<Token*>& tokens);
private:
	bool mdatalogProgram(std::deque<Token*>& tokens);
	bool scheme(std::deque<Token*>& tokens);
	bool schemeList(std::deque<Token*>& tokens);
	std::pair<bool, std::deque<parameter*>> idList(std::deque<Token*>& tokens);
	bool fact(std::deque<Token*>& tokens);
	bool factList(std::deque<Token*>& tokens);
	bool mrule(std::deque<Token*>& tokens);
	bool ruleList(std::deque<Token*>& tokens);
	std::pair<bool, predicate*> headPredicate(std::deque<Token*>& tokens);
	std::pair<bool, predicate*> mpredicate(std::deque<Token*>& tokens);
	std::pair<bool, std::deque<predicate*>> predicateList(std::deque<Token*>& tokens);
	std::pair<bool, parameter*> mparameter(std::deque<Token*>& tokens);
	std::pair<bool, std::deque<parameter*>> parameterList(std::deque<Token*>& tokens);
	std::pair<bool, expression*> mexpression(std::deque<Token*>& tokens);
	std::pair<bool, parameter*> moperator(std::deque<Token*>& tokens);
	bool query(std::deque<Token*>& tokens);
	bool queryList(std::deque<Token*>& tokens);
	std::pair<bool, std::deque<parameter*>> stringList(std::deque<Token*>& tokens);

	bool datalogSchemes(std::deque<Token*>& tokens);
	bool datalogRules(std::deque<Token*>& tokens);
	bool datalogFacts(std::deque<Token*>& tokens);
	bool datalogQueries(std::deque<Token*>& tokens);

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

private:
	datalogProgram program;
};

