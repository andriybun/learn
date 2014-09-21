#include "operator.h"
#include "token.h"

operatorInfoT::operatorInfoT(void)
{
}

operatorInfoT::~operatorInfoT(void)
{
}

operatorInfoT& operatorInfoT::Instance()
{
	static operatorInfoT _instance;
	return _instance;
}

void operatorInfoT::AddOperator(const std::string &name,
								const std::string &str,
								operatorInfoT::typeT type,
								int precedence,
								operatorInfoT::asociativityT asociativity,
								int numOperands)
{
	this->properties.insert(
		std::pair<std::string, propertiesT>(name, propertiesT(type, str, precedence, asociativity, numOperands)));
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

operatorInfoT::typeT operatorInfoT::getType(const std::string &name) const
{
	return this->FindOperator(name).type;
}

void operatorInfoT::Execute(const std::string &name, polishStackT<tokenT*> &ps, WorkspaceVariables &dict) const
{
	propertiesT prop = this->FindOperator(name);
	switch (prop.type)
	{
	case PLUS:
		this->doPlus(ps, dict);
		break;
	case MINUS:
		this->doMinus(ps, dict);
		break;
	case UNARY_MINUS:
		this->doUnaryMinus(ps, dict);
		break;
	case TIMES:
		this->doTimes(ps, dict);
		break;
	case DIVIDE:
		this->doDivide(ps, dict);
		break;
	case MODULO:
		this->doModulo(ps, dict);
		break;
	case POWER:
		this->doPower(ps, dict);
		break;
	case ASSIGN:
		this->doAssign(ps, dict);
		break;
	default:
		throw "Exception: operator not implemented";
	}
}

std::string operatorInfoT::AllOperatorsAsString() const
{
	std::string operatorStr;
	std::map<std::string, propertiesT>::const_iterator it = this->properties.begin();
	while (it != this->properties.end())
	{
		operatorStr += it->second.str;
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

void operatorInfoT::doPlus(polishStackT<tokenT*> &ps, WorkspaceVariables &dict) const
{
	this->CheckPolishVector(ps, 2);
	int a = ps.topVal(dict);
	ps.pop();
	int b = ps.topVal(dict);
	ps.pop();
	ps.push(new constantT(b + a));
}

void operatorInfoT::doMinus(polishStackT<tokenT*> &ps, WorkspaceVariables &dict) const
{
	this->CheckPolishVector(ps, 2);
	int a = ps.topVal(dict);
	ps.pop();
	int b = ps.topVal(dict);
	ps.pop();
	ps.push(new constantT(b - a));
}

void operatorInfoT::doTimes(polishStackT<tokenT*> &ps, WorkspaceVariables &dict) const
{
	this->CheckPolishVector(ps, 2);
	int a = ps.topVal(dict);
	ps.pop();
	int b = ps.topVal(dict);
	ps.pop();
	ps.push(new constantT(b * a));
}

void operatorInfoT::doDivide(polishStackT<tokenT*> &ps, WorkspaceVariables &dict) const
{
	this->CheckPolishVector(ps, 2);
	int a = ps.topVal(dict);
	ps.pop();
	int b = ps.topVal(dict);
	ps.pop();
	ps.push(new constantT(b / a));
}

void operatorInfoT::doModulo(polishStackT<tokenT*> &ps, WorkspaceVariables &dict) const
{
	this->CheckPolishVector(ps, 2);
	int a = ps.topVal(dict);
	ps.pop();
	int b = ps.topVal(dict);
	ps.pop();
	ps.push(new constantT(b % a));
}

void operatorInfoT::doPower(polishStackT<tokenT*> &ps, WorkspaceVariables &dict) const
{
	this->CheckPolishVector(ps, 2);
	int a = ps.topVal(dict);
	ps.pop();
	int b = ps.topVal(dict);
	ps.pop();
	int res = (int)ceil(pow((float)b, (float)a));
	ps.push(new constantT(res));
}

void operatorInfoT::doAssign(polishStackT<tokenT*> &ps, WorkspaceVariables &dict) const
{
	this->CheckPolishVector(ps, 2);
	int a = ps.topVal(dict);
	ps.pop();
	std::string lhsName = ps.topName();
	ps.pop();
	ps.push(new variableT(lhsName));
	dict.DictUpdate(lhsName, a);
}

void operatorInfoT::doUnaryMinus(polishStackT<tokenT*> &ps, WorkspaceVariables &dict) const
{
	this->CheckPolishVector(ps, 1);
	int a = ps.topVal(dict);
	ps.pop();
	ps.push(new constantT(-a));
}
