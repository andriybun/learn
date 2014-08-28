#pragma once

#include <string>

class operatorDataT
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
	typeT type;
	std::string name;
	int precedence;
	asociativityT asociativity;
public:
	operatorDataT(void);
	~operatorDataT(void);
};
