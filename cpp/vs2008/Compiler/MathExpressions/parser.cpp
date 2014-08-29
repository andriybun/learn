#include "parser.h"

parserT::parserT()
{
	this->InitializeOperatorPrecedence();
}

parserT::~parserT(void)
{
	this->ClearStack<tokenT*>(this->polishTokenStack);
}

template <class T>
void parserT::ClearStack(std::stack<T> &st)
{
	while (!st.empty())
	{
		delete st.top();
		st.pop();
	}
}

//template <> parserT::ClearStack<tokenT*>(stack<tokenT*> &st);

void parserT::EvaluateExpression(const std::string &expr)
{
	this->tokenVec.clear();
	this->ClearStack<tokenT*>(this->polishTokenStack);
	this->TokenizeExpression(expr);
	this->CompilePolishNotation();
}


void parserT::TokenizeExpression(const std::string &expr)
{
	std::stringstream stringStream(expr);
	std::string line;
	std::string ops = GetOperatorsAsString();
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
}

std::string parserT::GetOperatorsAsString()
{
	std::string operatorStr(" ()");
	std::map<std::string, operatorPropertiesT>::iterator it = this->operatorPrecedence.begin();
	while (it != this->operatorPrecedence.end())
	{
		operatorStr += it->first;
		++it;
	}
	return operatorStr;
}

void parserT::CompilePolishNotation()
{
	std::stack<std::string> stk;
	for (size_t i = 0; i < this->tokenVec.size(); i++)
	{
		std::string word = this->tokenVec[i];
		bool isVar = this->IsName(word);
		bool isNum = this->IsNumber(word);
		if (isVar)
		{
			this->polishVec.push_back(word);
			tokenT* tmp = new variableT(word);
			this->polishTokenStack.push(tmp);
		}
		else if (isNum)
		{
			this->polishVec.push_back(word);
			tokenT* tmp = new constantT(atoi(word.c_str()));
			this->polishTokenStack.push(tmp);
		}
		else if (!word.compare("("))
		{
			// TODO: include operators
			stk.push(word);
		}
		else if (!word.compare(")"))
		{
			while (stk.top().compare("("))
			{
				this->polishVec.push_back(stk.top());
				stk.pop();
				if (stk.empty())
				{
					throw "Error: parentheses";
				}
			}
			stk.pop();
		}
		else
		{
			std::map<std::string, operatorPropertiesT>::const_iterator currIt = this->operatorPrecedence.find(word);
			if (currIt == this->operatorPrecedence.end())
			{
				throw "Error: unknown symbol";
			}
			if (stk.empty() || !(stk.top().compare("(")))
			{
				stk.push(word);
			}
			else
			{
				std::map<std::string, operatorPropertiesT>::const_iterator stkIt = this->operatorPrecedence.find(stk.top());
				if ((stkIt->second.precedence < currIt->second.precedence) ||
					((stkIt->second.precedence == currIt->second.precedence) &&
					(currIt->second.asociativity == LEFT)))
				{
					this->polishVec.push_back(stk.top());
					stk.pop();
				}
				stk.push(word);
			}


		}
	}
	// Push the remaining tokens into the polish notation vector
	while (!stk.empty())
	{
		this->polishVec.push_back(stk.top());
		stk.pop();
	}
	printf("Polish vector:\n");
	for (size_t i = 0; i < this->polishVec.size(); i++)
	{
		printf("%s\n", this->polishVec[i].c_str());
	}
	printf("Polish token vector:\n");
	while (!this->polishTokenStack.empty())
	{
		std::cout << this->polishTokenStack.top()->getValue(this->varTable) << std::endl;
		polishTokenStack.pop();
	}
}

void parserT::AddVariable(const std::string &name, int val)
{
	this->varTable.insert(std::pair<std::string, int>(name, val));
}

bool parserT::IsNumber(const std::string &word)
{
	// TODO: allow floats
	std::string::const_iterator it = word.begin();
	std::locale loc;
	while (it != word.end() && std::isdigit(*it, loc)) ++it;
	return !word.empty() && it == word.end();
}

bool parserT::IsName(const std::string &word)
{
	std::string::const_iterator it = word.begin();
	std::locale loc;
	if (!std::isalpha(*it++, loc)) return false;
	while (it != word.end() && (std::isalpha(*it, loc) || std::isdigit(*it, loc))) ++it;
	return !word.empty() && it == word.end();
}