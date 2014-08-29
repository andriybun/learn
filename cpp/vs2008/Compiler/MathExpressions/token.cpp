#include "token.h"

int variableT::getValue(const std::map<std::string, int> &varTable,
			std::stack<tokenT*> &polishStack) const
{
    std::map<std::string, int>::const_iterator varData = varTable.find(this->name);
    if (varData == varTable.end())
    {
	throw "Error: variable not initialized";
    }
    return varData->second;
}

int constantT::getValue(const std::map<std::string, int> &varTable,
			std::stack<tokenT*> &polishStack) const
{
    return this->name;
}
