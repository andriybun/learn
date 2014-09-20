#pragma once

#include <map>
#include <string>
#include <sstream>
#include <stack>
#include <cstdio>
#include "operator.h"

//class operatorInfoT;

class tokenT
{
public:
	enum typeT 
	{
		VARIABLE,
		CONSTANT,
		OPERATOR
	};
	tokenT(void);
	virtual ~tokenT(void);
	virtual int getValue(const std::map<std::string, int> &varTable) const = 0;
	virtual std::string getName() const = 0;
	typeT getType();
protected:
	typeT tokenType;
};

class variableT : public tokenT
{
private:
	std::string name;
public:
	variableT(const std::string &name);
	~variableT(void);
	int getValue(const std::map<std::string, int> &varTable) const;
	std::string getName() const;
};

class constantT : public tokenT
{
private:
	int name;
public:
	constantT(const int name);
	~constantT(void);
	int getValue(const std::map<std::string, int> &varTable) const;
	std::string getName() const;
};


class operatorT : public tokenT
{
private:
	operatorInfoT::typeT type;
public:
	operatorT(std::string name);
	~operatorT(void); 
	int getValue(const std::map<std::string, int> &varTable) const;
	std::string getName() const;
};
