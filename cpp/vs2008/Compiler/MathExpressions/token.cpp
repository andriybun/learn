#include "token.h"

tokenT::tokenT(void) {}

tokenT::~tokenT(void) {}

tokenT::typeT tokenT::getType()
{
	return this->tokenType;
}

variableT::variableT(const std::string &name)
{
	this->name = name;
	this->tokenType = VARIABLE;
}

variableT::~variableT() {}

int variableT::getValue(const WorkspaceVariables &varTable) const
{
	if (boost::optional<int> val = varTable.DictFind(this->getName()))
	{
		return *val;
	}
	else
	{
		throw "Error: variable not initialized";
	}
}

std::string variableT::getName() const
{
	return this->name;
}

constantT::constantT(const int name)
{
	this->name = name;
	this->tokenType = CONSTANT;
}

constantT::~constantT() {}

int constantT::getValue(const WorkspaceVariables &varTable) const
{
	return this->name;
}

std::string constantT::getName() const
{
	std::stringstream ss;
	ss << this->name;
	return ss.str();
}

operatorT::operatorT(std::string name) 
{
	// TODO: this->type = ...
	this->tokenType = OPERATOR;
}

operatorT::~operatorT() {}

int operatorT::getValue(const WorkspaceVariables &varTable) const
{
	throw "Error: operator doesn't have value";
	return -1;
}

std::string operatorT::getName() const
{
	throw "Error: not implemented";
	return std::string();
}