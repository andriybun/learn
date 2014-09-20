#pragma once

#include <map>
#include <string>
#include <sstream>
#include <stack>
#include <vector>
#include <iostream>

#include "common.h"
#include "operator.h"
#include "token.h"
#include "polish_stack.h"
#include "fsm.h"

#include "boost/foreach.hpp"
#define _foreach BOOST_FOREACH

class fsm;

class parserT
{
private:
	operatorInfoT operatorData;
	std::vector<std::string> tokenVec;
	polishStackT<tokenT*> polishTokenStack;

	void InitializeOperatorPrecedence()
	{
		this->operatorData.AddOperator("+", operatorInfoT::PLUS, 6, operatorInfoT::LEFT, 2);
		this->operatorData.AddOperator("-", operatorInfoT::MINUS, 6, operatorInfoT::LEFT, 2);
		//this->operatorData.AddOperator("-", operatorT::UNARY_MINUS, 3, operatorT::RIGHT, 1);
		this->operatorData.AddOperator("*", operatorInfoT::TIMES, 5, operatorInfoT::LEFT, 2);
		this->operatorData.AddOperator("/", operatorInfoT::DIVIDE, 5, operatorInfoT::LEFT, 2);
		this->operatorData.AddOperator("%", operatorInfoT::MODULO, 5, operatorInfoT::LEFT, 2);
		this->operatorData.AddOperator("^", operatorInfoT::POWER, 4, operatorInfoT::RIGHT, 2);
		this->operatorData.AddOperator("=", operatorInfoT::ASSIGN, 15, operatorInfoT::RIGHT, 2);
	}
	void TokenizeExpression(const std::string &expr);
	void CompilePolishNotation();
	void ProcessPolishVector();
	void ClearStack(polishStackT<tokenT*> &st);
public:
	parserT();
	~parserT(void);

	void EvaluateExpression(const std::string &expr);
	void AddVariable(const std::string &name, int val);

	friend class fsm;
};
