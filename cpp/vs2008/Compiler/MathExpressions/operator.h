#pragma once

#include <map>
#include <stack>
#include <string>
#include "token.h"

class operatorT
{
public:
	enum typeT
	{
		PLUS,
		MINUS,
		TIMES,
		DIVIDE,
		POWER,
		ASSIGN
	};
	enum asociativityT
	{
		LEFT,
		RIGHT
	};
private:
	struct propertiesT
	{
	    typeT type;
	    int precedence;
	    asociativityT asociativity;
	propertiesT(typeT type, 
		    int precedence, 
		    asociativityT asociativity),
	    : type(type), 
		precedence(precedence), 
		asociativity(asociativity)
	        {};
	    
	}
	std::map<std::string, propertiesT> properties;

	void doPlus(std::stack<tokenT*> &s);
	void doMinus(std::stack<tokenT*> &s);
	void doTimes(std::stack<tokenT*> &s);
	void doDivide(std::stack<tokenT*> &s);
	void doPower(std::stack<tokenT*> &s);
	void doAssign(std::stack<tokenT*> &s);
public:
	operatorDataT(void);
	~operatorDataT(void);
	void AddOperator(const std::string &name, typeT type, int precedence, asociativityT asociativity);
	void Execute(const std::string &name, std::stack<tokenT*> &polishTokenStack) const;
};
