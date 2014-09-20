#include "parser.h"

parserT::parserT()
{
	this->operatorInfo = &(operatorInfoT::Instance());
	this->InitializeOperatorPrecedence();
}

parserT::~parserT(void)
{
    this->ClearStack(this->polishTokenStack);
}

void parserT::ClearStack(polishStackT<tokenT*> &st)
{
	while (!st.empty())
	{
		delete st.top();
		st.pop();
	}
}

void parserT::EvaluateExpression(const std::string &expr)
{
	this->tokenVec.clear();
	this->ClearStack(this->polishTokenStack);
	this->TokenizeExpression(expr);
	this->CompilePolishNotation();
}


void parserT::TokenizeExpression(const std::string &expr)
{
	std::stringstream stringStream(expr);
	std::string line;
	std::string ops = this->operatorInfo->AllOperatorsAsString() + " ()";
	while(std::getline(stringStream, line)) 
	{
		std::size_t prev = 0, pos;
		while ((pos = line.find_first_of(ops.c_str(), prev)) != std::string::npos)
		{
			if (pos > prev)
			{
				this->tokenVec.push_back(line.substr(prev, pos-prev));
			}
			std::string opPos = line.substr(pos, 1);
			if (opPos.compare(" "))
			{
				this->tokenVec.push_back(opPos);
			}
			prev = pos+1;
		}
		if (prev < line.length())
			this->tokenVec.push_back(line.substr(prev, std::string::npos));
	}
	FiniteStateMachine fsm;
	for (size_t i = 0; i < this->tokenVec.size(); i++)
	{
		this->tokenVec[i] = fsm.processToken(this->tokenVec[i]);
	}
}

void parserT::CompilePolishNotation()
{
	std::stack<std::string> stk;

	_foreach(std::string word, this->tokenVec)
	{
		bool isVar = IsName(word);
		bool isNum = IsNumber(word);
		if (isVar)
		{
			this->polishTokenStack.push(new variableT(word));
		}
		else if (isNum)
		{
			this->polishTokenStack.push(new constantT(atoi(word.c_str())));
		}
		else if (!word.compare("("))
		{
			stk.push(word);
		}
		else if (!word.compare(")"))
		{
			while (!stk.empty() && stk.top().compare("("))
			{
				this->operatorInfo->Execute(stk.top(), this->polishTokenStack);
				stk.pop();
				if (stk.empty())
				{
					throw "Error: unbalanced parentheses";
				}
			}
			if (stk.empty())
			{
				throw "Error: unbalanced parentheses";
			}
			stk.pop();
		}
		else
		{
			operatorInfoT::propertiesT operProp = this->operatorInfo->FindOperator(word);
			if (stk.empty() || !(stk.top().compare("(")))
			{
				stk.push(word);
			}
			else
			{
				operatorInfoT::propertiesT stkOperProp = this->operatorInfo->FindOperator(stk.top());
				if ((stkOperProp.precedence < operProp.precedence) ||
					((stkOperProp.precedence == operProp.precedence) &&
					(operProp.asociativity == operatorInfoT::LEFT)))
				{
					this->operatorInfo->Execute(stk.top(), this->polishTokenStack);
					stk.pop();
				}
				stk.push(word);
			}
		}
	}
	// Execute the remaining operations
	while (!stk.empty())
	{
		this->operatorInfo->Execute(stk.top(), this->polishTokenStack);
		stk.pop();
	}
	// Check if the resulting polish stack doesn't contain 1 element, then error
	if (this->polishTokenStack.size() != 1)
	{
		throw "Error: wrong expression";
	}
	// Print result
	printf("Result: %d\n", this->polishTokenStack.topVal());
}

void parserT::AddVariable(const std::string &name, int val)
{
	this->polishTokenStack.DictInsert(name, val);
}

