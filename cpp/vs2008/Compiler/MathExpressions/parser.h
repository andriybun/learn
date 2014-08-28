#pragma once

#include <locale>
#include <map>
#include <string>
#include <sstream>
#include <stack>
#include <vector>
#include <iostream>

#include "token.h"


class parserT
{
public:
	enum opAsociativityT
	{
		LEFT,
		RIGHT
	};
	struct operatorPropertiesT
	{
		int precedence;
		opAsociativityT asociativity;
		operatorPropertiesT(int pr, opAsociativityT as): precedence(pr), asociativity(as) {};
	};
private:
	std::map<std::string, operatorPropertiesT> operatorPrecedence;
	std::vector<std::string> tokenVec, polishVec;
	std::vector<tokenT*> polishTokenVec;
	
	void InitializeOperatorPrecedence()
	{
		this->operatorPrecedence.insert(std::pair<std::string, operatorPropertiesT>("+", operatorPropertiesT(6, LEFT)));
		this->operatorPrecedence.insert(std::pair<std::string, operatorPropertiesT>("-", operatorPropertiesT(6, LEFT)));
		this->operatorPrecedence.insert(std::pair<std::string, operatorPropertiesT>("*", operatorPropertiesT(5, LEFT)));
		this->operatorPrecedence.insert(std::pair<std::string, operatorPropertiesT>("/", operatorPropertiesT(5, LEFT)));
		this->operatorPrecedence.insert(std::pair<std::string, operatorPropertiesT>("%", operatorPropertiesT(5, LEFT)));
		this->operatorPrecedence.insert(std::pair<std::string, operatorPropertiesT>("^", operatorPropertiesT(4, RIGHT)));
		this->operatorPrecedence.insert(std::pair<std::string, operatorPropertiesT>("=", operatorPropertiesT(15, RIGHT)));
	}
	std::string GetOperatorsAsString();
	void TokenizeExpression(const std::string &expr);
	void CompilePolishNotation();
	void ProcessPolishVector();
	void ClearPolishVector();
public:
	parserT();
	~parserT(void);

	void EvaluateExpression(const std::string &expr);
	
	static bool IsNumber(const std::string &word);
	static bool IsName(const std::string &word);
};
