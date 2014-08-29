#include "operator.h"

operatorT::operatorT(void)
{
}

operatorT::~operatorT(void)
{
}

void operatorT::AddOperator(const std::string &name, operatorT::typeT type, int precedence, operatorT::asociativityT asociativity)
{
    
    this->properties.insert(
	pair<std::string, this->propertiesT>(name, 
	     propertiesT(type, precedence, asociativity)));
}

void operatorT::Execute(const std::string &name, std::stack<tokenT*> &polishTokenStack) const
{
    std::map<std::string, propertiesT>::const_iterator oper = this->properties.find(name);
    if (oper == this->properties.end())
    {
	throw "Error: unknown operator";
    }
    else
    {
	switch (oper->second.type)
	{
	case PLUS:

	    break;
	case MINUS:

	    break;
	case TIMES:

	    break;
	case DIVIDE:

	    break;
	case POWER:
	    
	    break;
	case ASSIGN:

	    break;
	default:
	    throw "Exception: operator not implemented";
	}
    }

}

void operatorT::doPlus(std::stack<tokenT*> &s)
{
    
}

void operatorT::doMinus(std::stack<tokenT*> &s)
{

}

void operatorT::doTimes(std::stack<tokenT*> &s)
{

}

void operatorT::doDivide(std::stack<tokenT*> &s)
{

}

void operatorT::doPower(std::stack<tokenT*> &s)
{

}

void operatorT::doAssign(std::stack<tokenT*> &s)
{

}
