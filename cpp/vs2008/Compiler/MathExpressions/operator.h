#pragma once

#include <map>
#include <math.h>
#include <stack>
#include <string>
#include "polish_stack.h"

class tokenT;

// TODO: Singleton!
class operatorInfoT
{
public:
	enum typeT
	{
		PLUS,
		MINUS,
		UNARY_MINUS,
		TIMES,
		DIVIDE,
		MODULO,
		POWER,
		ASSIGN
	};
	enum asociativityT
	{
		LEFT,
		RIGHT
	};
	struct propertiesT
	{
		typeT type;
		int precedence;
		asociativityT asociativity;
		int numOperands;
		propertiesT(typeT type, 
			int precedence, 
			asociativityT asociativity,
			int numOperands) : 
		type(type), precedence(precedence), asociativity(asociativity), numOperands(numOperands) {};
	};

private:
	std::map<std::string, propertiesT> properties;

	void doPlus(polishStackT<tokenT*> &ps) const;
	void doMinus(polishStackT<tokenT*> &ps) const;
	void doTimes(polishStackT<tokenT*> &ps) const;
	void doDivide(polishStackT<tokenT*> &ps) const;
	void doModulo(polishStackT<tokenT*> &ps) const;
	void doPower(polishStackT<tokenT*> &ps) const;
	void doAssign(polishStackT<tokenT*> &ps) const;

	void CheckPolishVector(polishStackT<tokenT*> &ps, size_t n) const;
public:
	operatorInfoT(void);
	~operatorInfoT(void);
	void AddOperator(
		const std::string &name, 
		typeT type, 
		int precedence, 
		asociativityT asociativity,
		int numOperands);
	propertiesT FindOperator(const std::string &name) const;
	std::string GetAsString() const;
	void Execute(const std::string &name, polishStackT<tokenT*> &ps) const;
};
