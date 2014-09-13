#pragma once

#include <locale>
#include <map>
#include <string>
#include <sstream>
#include <stack>
#include <vector>
#include <iostream>

#include "operator.h"
#include "polish_stack.h"
#include "token.h"


class parserT
{
private:
	operatorT operatorData;
	std::vector<std::string> tokenVec;
	polishStackT<tokenT*> polishTokenStack;

	void InitializeOperatorPrecedence()
	{
		this->operatorData.AddOperator("+", operatorT::PLUS, 6, operatorT::LEFT);
		this->operatorData.AddOperator("-", operatorT::MINUS, 6, operatorT::LEFT);
		this->operatorData.AddOperator("*", operatorT::TIMES, 5, operatorT::LEFT);
		this->operatorData.AddOperator("/", operatorT::DIVIDE, 5, operatorT::LEFT);
		this->operatorData.AddOperator("%", operatorT::MODULO, 5, operatorT::LEFT);
		this->operatorData.AddOperator("^", operatorT::POWER, 4, operatorT::RIGHT);
		this->operatorData.AddOperator("=", operatorT::ASSIGN, 15, operatorT::RIGHT);
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
	static bool IsNumber(const std::string &word);
	static bool IsName(const std::string &word);
};
