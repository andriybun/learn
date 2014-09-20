#include "fsm.h"

FiniteStateMachine::FiniteStateMachine(void)
{
	this->current = new st0;
}

FiniteStateMachine::~FiniteStateMachine(void)
{
	delete this->current;
}

void FiniteStateMachine::setCurrent(State *s)
{
	this->current = s;
}

std::string FiniteStateMachine::processToken(const std::string &token)
{
	return this->current->processToken(this, token);
}

std::string st0::processToken(fsmT* fsm, const std::string &token)
{
	// Beginning of expression. May start with variable to be assigned to.
	if (IsName(token))
	{
		fsm->setCurrent(new st1);
		delete this;
	}
	else
	{
		throw "Error: Mathematical expression must start with a name of variable to be assigned to";
	}
	return token;
}

std::string st1::processToken(fsmT* fsm, const std::string &token)
{
	// After first variable in expression assignment operator is expected
	if (!token.compare("="))
	{
		fsm->setCurrent(new st2);
		delete this;
	}
	else
	{
		throw "Error: assignment operator expected";
	}
	return token;
}

std::string st2::processToken(fsmT* fsm, const std::string &token)
{
	// Operand expected: name, constant, unary minus or opening parenthesis
	if (IsName(token) || IsNumber(token))
	{
		fsm->setCurrent(new st3);
		delete this;
	}
	else if (!token.compare("-"))
	{
		fsm->setCurrent(new st4);
		delete this;
		return std::string("u-");
	}
	else if (!token.compare("("))
	{
		// State remains the same
	}
	else
	{
		throw "Error: Wrong operand. Variable or constant expected";
	}
	return token;
}

std::string st3::processToken(fsmT* fsm, const std::string &token)
{
	std::string ops("+-*/%^");
	if (!token.compare(")"))
	{
		fsm->setCurrent(new st3);
		delete this;
	}
	else if (ops.find(token) != std::string::npos)
	{
		// TODO: operatorData.GetAsString()
		fsm->setCurrent(new st2);
		delete this;
	}
	else
	{
		throw "Error: Operation expected";
	}
	return token;
}

std::string st4::processToken(fsmT* fsm, const std::string &token)
{
	if (IsName(token) || IsNumber(token))
	{
		fsm->setCurrent(new st3);
		delete this;
	}
	else if (!token.compare("("))
	{
		fsm->setCurrent(new st2);
		delete this;
	}
	else
	{
		throw "Error: Operand expected after unary minus";
	}
	return token;
}