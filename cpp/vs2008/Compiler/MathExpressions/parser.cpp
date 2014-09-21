#include "parser.h"

parserT::parserT()
{
	this->operatorInfo = &(operatorInfoT::Instance());
	this->fsm.InitializeOperatorInfo(this);
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
	this->fsm.reset();
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
	for (size_t i = 0; i < this->tokenVec.size(); i++)
	{
		this->tokenVec[i] = fsm.processToken(this->tokenVec[i]);
	}
}

void parserT::CompilePolishNotation()
{
	std::stack<std::string> operatorStack;

	foreach_(std::string word, this->tokenVec)
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
			operatorStack.push(word);
		}
		else if (!word.compare(")"))
		{
			while (!operatorStack.empty() && operatorStack.top().compare("("))
			{
				this->operatorInfo->Execute(operatorStack.top(), this->polishTokenStack, this->dict);
				operatorStack.pop();
				if (operatorStack.empty())
				{
					throw "Error: unbalanced parentheses";
				}
			}
			if (operatorStack.empty())
			{
				throw "Error: unbalanced parentheses";
			}
			operatorStack.pop();
		}
		else
		{
			operatorInfoT::propertiesT operProp = this->operatorInfo->FindOperator(word);
			if (operatorStack.empty() || !(operatorStack.top().compare("(")))
			{
				operatorStack.push(word);
			}
			else
			{
				operatorInfoT::propertiesT stkOperProp = this->operatorInfo->FindOperator(operatorStack.top());
				if ((stkOperProp.precedence < operProp.precedence) ||
					((stkOperProp.precedence == operProp.precedence) &&
					(operProp.asociativity == operatorInfoT::LEFT)))
				{
					this->operatorInfo->Execute(operatorStack.top(), this->polishTokenStack, this->dict);
					operatorStack.pop();
				}
				operatorStack.push(word);
			}
		}
	}
	// Execute the remaining operations
	while (!operatorStack.empty())
	{
		this->operatorInfo->Execute(operatorStack.top(), this->polishTokenStack, this->dict);
		operatorStack.pop();
	}
	// Check if the resulting polish stack doesn't contain 1 element, then error
	if (this->polishTokenStack.size() != 1)
	{
		throw "Error: wrong expression";
	}
	// Print result
	printf("Result: %d\n", this->polishTokenStack.topVal(this->dict));
}

void parserT::AddVariable(const std::string &name, int val)
{
	this->dict.DictInsert(name, val);
}

