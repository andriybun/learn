#pragma once

#include <string>
#include <cstdio>
#include "operatorDataT.h"

class tokenT
{
public:
	tokenT(void) {/*printf("construct\n");*/};
	virtual ~tokenT(void) {/*printf("deconstruct\n");*/};
};

class variableT : public tokenT
{
private:
	std::string name;
public:
	variableT(const std::string &name): name(name) {};
	~variableT(void) {};
};

class constantT : public tokenT
{
private:
	int name;
public:
	constantT(const int name): name(name) {};
	~constantT(void) {};
};

class operatorT : tokenT
{
private:
	operatorDataT::typeT name;
public:
	operatorT(operatorDataT::typeT name): name(name) {};
	~operatorT(void) {}; 
};