#include "token.h"

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
	return name;
}

int constantT::getValue(const std::map<std::string, int> &varTable) const
{
	return this->name;
}

std::string constantT::getName() const
{
	throw "Error: constant can't have a name";
	return std::string("Error");
}

//int operatorStrT::getValue(const std::map<std::string, int> &varTable) const
//{
//	throw "Error: operator doesn't have value";
//	return -1;
//}

//std::string operatorStrT ::getName() const
//{
//	return this->name;
//}