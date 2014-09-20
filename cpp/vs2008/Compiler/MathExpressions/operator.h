#pragma once

#include <map>
#include <math.h>
#include <stack>
#include <string>
#include "common.h"
#include "polish_stack.h"

class tokenT;

// This class is a singleton
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
		std::string str;
		int precedence;
		asociativityT asociativity;
		int numOperands;
		propertiesT(
			typeT type,
			std::string str,
			int precedence, 
			asociativityT asociativity,
			int numOperands) : 
		type(type), 
			str(str), 
			precedence(precedence), 
			asociativity(asociativity), 
			numOperands(numOperands) {};
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
	void doUnaryMinus(polishStackT<tokenT*> &ps) const;

	void CheckPolishVector(polishStackT<tokenT*> &ps, size_t n) const;
	operatorInfoT(void);
public:
	~operatorInfoT(void);
	void AddOperator(
		const std::string &name, 
		const std::string &str, 
		typeT type, 
		int precedence, 
		asociativityT asociativity,
		int numOperands);
	propertiesT FindOperator(const std::string &name) const;
	typeT getType(const std::string &name) const;
	std::string AllOperatorsAsString() const;
	void Execute(const std::string &name, polishStackT<tokenT*> &ps) const;
	static operatorInfoT& Instance();
};
