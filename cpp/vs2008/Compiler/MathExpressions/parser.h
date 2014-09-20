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

class fsm;

class parserT
{
private:
	operatorInfoT* operatorInfo;
	std::vector<std::string> tokenVec;
	polishStackT<tokenT*> polishTokenStack;

	void InitializeOperatorPrecedence()
	{
		this->operatorInfo->AddOperator("+",  "+", operatorInfoT::PLUS, 6, operatorInfoT::LEFT, 2);
		this->operatorInfo->AddOperator("-",  "-", operatorInfoT::MINUS, 6, operatorInfoT::LEFT, 2);
		this->operatorInfo->AddOperator("u-", "-", operatorInfoT::UNARY_MINUS, 3, operatorInfoT::RIGHT, 1);
		this->operatorInfo->AddOperator("*",  "*", operatorInfoT::TIMES, 5, operatorInfoT::LEFT, 2);
		this->operatorInfo->AddOperator("/",  "/", operatorInfoT::DIVIDE, 5, operatorInfoT::LEFT, 2);
		this->operatorInfo->AddOperator("%",  "%", operatorInfoT::MODULO, 5, operatorInfoT::LEFT, 2);
		this->operatorInfo->AddOperator("^",  "^", operatorInfoT::POWER, 4, operatorInfoT::RIGHT, 2);
		this->operatorInfo->AddOperator("=",  "=", operatorInfoT::ASSIGN, 15, operatorInfoT::RIGHT, 2);
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
