#pragma once

#include <map>
#include <string>
#include <stack>
#include <cstdio>
#include "operator.h"

class tokenT
{
public:
	tokenT(void) {};
	~tokenT(void) {};
	virtual int getValue(
		const std::map<std::string, int> &varTable,
		std::stack<tokenT*> &polishStack) const = 0;
};

class variableT : public tokenT
{
private:
	std::string name;
public:
	variableT(const std::string &name): name(name) {};
	~variableT(void) {};
	int getValue(
		const std::map<std::string, int> &varTable,
		std::stack<tokenT*> &polishStack) const;
};

class constantT : public tokenT
{
private:
	int name;
public:
	constantT(const int name): name(name) {};
	~constantT(void) {};
	int getValue(
		const std::map<std::string, int> &varTable,
		std::stack<tokenT*> &polishStack) const;
};

/*
class operatorT : tokenT
{
private:
	operatorDataT::typeT name;
public:
	operatorT(operatorDataT::typeT name): name(name) {};
	~operatorT(void) {}; 
	int getValue(
		const std::map<std::string, int> &varTable,
		std::stack<tokenT*> &polishStack) const;

};
*/
