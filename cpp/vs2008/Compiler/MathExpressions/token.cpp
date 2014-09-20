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

int variableT::getValue(const std::map<std::string, int> &varTable) const
{
	std::map<std::string, int>::const_iterator varData = varTable.find(this->name);
	if (varData == varTable.end())
	{
		throw "Error: variable not initialized";
	}
	return varData->second;
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

int constantT::getValue(const std::map<std::string, int> &varTable) const
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

int operatorT::getValue(const std::map<std::string, int> &varTable) const
{
	throw "Error: operator doesn't have value";
	return -1;
}

std::string operatorT::getName() const
{
	throw "Error: not implemented";
	return std::string();
}