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
		std::pair<std::string, propertiesT>(name, propertiesT(type, precedence, asociativity)));
}

operatorT::propertiesT operatorT::FindOperator(const std::string &name) const
{
	std::map<std::string, propertiesT>::const_iterator oper = this->properties.find(name);
	if (oper == this->properties.end())
	{
		throw "Error: unknown operator";
	}
	return oper->second;
}

void operatorT::Execute(const std::string &name, polishStackT<tokenT*> &ps) const
{
	propertiesT prop = this->FindOperator(name);
	switch (prop.type)
	{
	case PLUS:
		this->doPlus(ps);
		break;
	case MINUS:
		this->doMinus(ps);
		break;
	case TIMES:
		this->doTimes(ps);
		break;
	case DIVIDE:
		this->doDivide(ps);
		break;
	case MODULO:
		this->doModulo(ps);
		break;
	case POWER:
		this->doPower(ps);
		break;
	case ASSIGN:
		this->doAssign(ps);
		break;
	default:
		throw "Exception: operator not implemented";
	}
}

std::string operatorT::GetAsString() const
{
	std::string operatorStr(" ()");
	std::map<std::string, propertiesT>::const_iterator it = this->properties.begin();
	while (it != this->properties.end())
	{
		operatorStr += it->first;
		++it;
	}
	return operatorStr;
}

void operatorT::CheckPolishVector(polishStackT<tokenT*> &ps, size_t n) const
{
	if (ps.size() < n)
	{
		throw "Error: too many operators";
	}
}

void operatorT::doPlus(polishStackT<tokenT*> &ps) const
{
	CheckPolishVector(ps, 2);
	int a = ps.topVal();
	ps.pop();
	int b = ps.topVal();
	ps.pop();
	ps.push(new constantT(b + a));
}

void operatorT::doMinus(polishStackT<tokenT*> &ps) const
{
	CheckPolishVector(ps, 2);
	int a = ps.topVal();
	ps.pop();
	int b = ps.topVal();
	ps.pop();
	ps.push(new constantT(b - a));
}

void operatorT::doTimes(polishStackT<tokenT*> &ps) const
{
	CheckPolishVector(ps, 2);
	int a = ps.topVal();
	ps.pop();
	int b = ps.topVal();
	ps.pop();
	ps.push(new constantT(b * a));
}

void operatorT::doDivide(polishStackT<tokenT*> &ps) const
{
	CheckPolishVector(ps, 2);
	int a = ps.topVal();
	ps.pop();
	int b = ps.topVal();
	ps.pop();
	ps.push(new constantT(b / a));
}

void operatorT::doModulo(polishStackT<tokenT*> &ps) const
{
	CheckPolishVector(ps, 2);
	int a = ps.topVal();
	ps.pop();
	int b = ps.topVal();
	ps.pop();
	ps.push(new constantT(b % a));
}

void operatorT::doPower(polishStackT<tokenT*> &ps) const
{
	CheckPolishVector(ps, 2);
	int a = ps.topVal();
	ps.pop();
	int b = ps.topVal();
	ps.pop();
	int res = (int)ceil(pow((float)b, (float)a));
	ps.push(new constantT(res));
}

void operatorT::doAssign(polishStackT<tokenT*> &ps) const
{
	CheckPolishVector(ps, 2);
	int a = ps.topVal();
	ps.pop();
	std::string lhsName = ps.topName();
	ps.pop();
	ps.push(new variableT(lhsName));
	ps.DictUpdate(lhsName, a);
}
