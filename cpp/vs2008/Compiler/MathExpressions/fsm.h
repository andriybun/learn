#pragma once

#include <string>
#include "common.h"
#include "polish_stack.h"
#include "token.h"

class FiniteStateMachine;
class parserT;
typedef FiniteStateMachine fsmT;

class State
{
private:
	
public:
	virtual std::string processToken(fsmT*, const std::string &, tokenT::typeT &) = 0;
};

struct exceptT
{
	std::string msg;
	State* obj;
	exceptT(const char* msg, State* obj) : msg(msg), obj(obj) {};
};

class st0 : public State
{
	std::string processToken(fsmT*, const std::string &, tokenT::typeT &);
};

class st1 : public State
{
	std::string processToken(fsmT*, const std::string &, tokenT::typeT &);
};

class st2 : public State
{
	std::string processToken(fsmT*, const std::string &, tokenT::typeT &);
};

class st3 : public State
{
	std::string processToken(fsmT*, const std::string &, tokenT::typeT &);
};

class st4 : public State
{
	std::string processToken(fsmT*, const std::string &, tokenT::typeT &);
};

class FiniteStateMachine
{
	polishStackT<tokenT*> polishStack;
	class State *current;
public:
	FiniteStateMachine(void);
	~FiniteStateMachine(void);
	void InitializeOperatorInfo(parserT* interpreter) const;

	void reset();
	void setCurrent(State *s);
	std::string processToken(const std::string &);
};
