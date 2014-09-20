#pragma once

#include <string>
#include "common.h"
#include "parser.h"

class FiniteStateMachine;
typedef FiniteStateMachine fsmT;

class State
{
private:
	
public:
	virtual void processToken(fsmT*, const std::string &) = 0;
};

struct exceptT
{
	std::string msg;
	State* obj;
	exceptT(const char* msg, State* obj) : msg(msg), obj(obj) {};
};

class st0 : public State
{
	void processToken(fsmT*, const std::string &);
};

class st1 : public State
{
	void processToken(fsmT*, const std::string &);
};

class st2 : public State
{
	void processToken(fsmT*, const std::string &);
};

class st3 : public State
{
	void processToken(fsmT*, const std::string &);
};

class st4 : public State
{
	void processToken(fsmT*, const std::string &);
};

class FiniteStateMachine
{
	class State *current;
public:
	FiniteStateMachine(void);
	~FiniteStateMachine(void);

	void setCurrent(State *s);
	void processToken(const std::string &);
};
