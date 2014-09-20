#include "operator.h"
#include "token.h"

operatorInfoT::operatorInfoT(void)
{
}

operatorInfoT::~operatorInfoT(void)
{
}

void operatorInfoT::AddOperator(const std::string &name,
							operatorInfoT::typeT type,
							int precedence,
							operatorInfoT::asociativityT asociativity,
							int numOperands)
{
	this->properties.insert(
		std::pair<std::string, propertiesT>(name, propertiesT(type, precedence, asociativity, numOperands)));
}

operatorInfoT::propertiesT operatorInfoT::FindOperator(const std::string &name) const
{
	std::map<std::string, propertiesT>::const_iterator oper = this->properties.find(name);
	if (oper == this->properties.end())
	{
		throw "Error: unknown operator";
	}
	return oper->second;
}

void operatorInfoT::Execute(const std::string &name, polishStackT<tokenT*> &ps) const
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

std::string operatorInfoT::GetAsString() const
{
	std::string operatorStr;
	std::map<std::string, propertiesT>::const_iterator it = this->properties.begin();
	while (it != this->properties.end())
	{
		operatorStr += it->first;
		++it;
	}
	return operatorStr;
}

void operatorInfoT::CheckPolishVector(polishStackT<tokenT*> &ps, size_t n) const
{
	if (ps.size() < n)
	{
		throw "Error: too many operators";
	}
}

void operatorInfoT::doPlus(polishStackT<tokenT*> &ps) const
{
	this->CheckPolishVector(ps, 2);
	int a = ps.topVal();
	ps.pop();
	int b = ps.topVal();
	ps.pop();
	ps.push(new constantT(b + a));
}

void operatorInfoT::doMinus(polishStackT<tokenT*> &ps) const
{
	this->CheckPolishVector(ps, 2);
	int a = ps.topVal();
	ps.pop();
	int b = ps.topVal();
	ps.pop();
	ps.push(new constantT(b - a));
}

void operatorInfoT::doTimes(polishStackT<tokenT*> &ps) const
{
	this->CheckPolishVector(ps, 2);
	int a = ps.topVal();
	ps.pop();
	int b = ps.topVal();
	ps.pop();
	ps.push(new constantT(b * a));
}

void operatorInfoT::doDivide(polishStackT<tokenT*> &ps) const
{
	this->CheckPolishVector(ps, 2);
	int a = ps.topVal();
	ps.pop();
	int b = ps.topVal();
	ps.pop();
	ps.push(new constantT(b / a));
}

void operatorInfoT::doModulo(polishStackT<tokenT*> &ps) const
{
	this->CheckPolishVector(ps, 2);
	int a = ps.topVal();
	ps.pop();
	int b = ps.topVal();
	ps.pop();
	ps.push(new constantT(b % a));
}

void operatorInfoT::doPower(polishStackT<tokenT*> &ps) const
{
	this->CheckPolishVector(ps, 2);
	int a = ps.topVal();
	ps.pop();
	int b = ps.topVal();
	ps.pop();
	int res = (int)ceil(pow((float)b, (float)a));
	ps.push(new constantT(res));
}

void operatorInfoT::doAssign(polishStackT<tokenT*> &ps) const
{
	this->CheckPolishVector(ps, 2);
	int a = ps.topVal();
	ps.pop();
	std::string lhsName = ps.topName();
	ps.pop();
	ps.push(new variableT(lhsName));
	ps.DictUpdate(lhsName, a);
}
