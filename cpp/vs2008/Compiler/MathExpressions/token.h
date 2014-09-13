#pragma once

#include <map>
#include <string>
#include <stack>
#include <cstdio>

class tokenT
{
public:
	tokenT(void) {};
	virtual ~tokenT(void) {};
	virtual int getValue(const std::map<std::string, int> &varTable) const = 0;
	virtual std::string getName() const = 0;
};

class variableT : public tokenT
{
private:
	std::string name;
public:
	variableT(const std::string &name): name(name) {};
	~variableT(void) {};
	int getValue(const std::map<std::string, int> &varTable) const;
	std::string getName() const;
};

class constantT : public tokenT
{
private:
	int name;
public:
	constantT(const int name): name(name) {};
	~constantT(void) {};
	int getValue(const std::map<std::string, int> &varTable) const;
	std::string getName() const;
};


//class operatorStrT : public tokenT
//{
//private:
//	std::string name;
//public:
//	operatorStrT(std::string name): name(name) {};
//	~operatorStrT(void) {}; 
//	int getValue(const std::map<std::string, int> &varTable) const;
//	std::string getName() const;
//};
