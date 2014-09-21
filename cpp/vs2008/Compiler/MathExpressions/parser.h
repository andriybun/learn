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
#include "workspace_variables.h"
#include "fsm.h"

class parserT
{
private:
	operatorInfoT* operatorInfo;
	std::vector<std::string> tokenVec;
	polishStackT<tokenT*> polishTokenStack;
	WorkspaceVariables dict;
	FiniteStateMachine fsm;

	void TokenizeExpression(const std::string &expr);
	void CompilePolishNotation();
	void ProcessPolishVector();
	void ClearStack(polishStackT<tokenT*> &st);
public:
	parserT();
	~parserT(void);

	void EvaluateExpression(const std::string &expr);
	void AddVariable(const std::string &name, int val);

	friend class FiniteStateMachine;
};
