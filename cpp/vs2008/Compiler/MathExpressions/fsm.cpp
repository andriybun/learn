#include "fsm.h"
#include "parser.h"

FiniteStateMachine::FiniteStateMachine(void)
{
	this->current = new st0;
}

FiniteStateMachine::~FiniteStateMachine(void)
{
	delete this->current;
}

void FiniteStateMachine::reset()
{
	delete this->current;
	this->setCurrent(new st0);
	// Clear polish stack
	while (!this->polishStack.empty())
	{
		delete this->polishStack.top();
		this->polishStack.pop();
	}
}

void FiniteStateMachine::setCurrent(State *s)
{
	this->current = s;
}

std::string FiniteStateMachine::processToken(const std::string &token)
{
	tokenT::typeT type;
	std::string out = this->current->processToken(this, token, type);
	std::string tokenType;
	switch (type)
	{
	case tokenT::VARIABLE:
		tokenType = "VARIABLE";
		break;
	case tokenT::CONSTANT:
		tokenType = "CONSTANT";
		break;
	case tokenT::OPERATOR:
		tokenType = "OPERATOR";
		break;
	}
	std::cout << out << "\t" << tokenType << std::endl;
	return out;
}


//////////////////////////////////////////////////////////////////////////
// Possible states
//////////////////////////////////////////////////////////////////////////

std::string st0::processToken(fsmT* fsm, const std::string &token, tokenT::typeT &type)
{
	// Beginning of expression. May start with variable to be assigned to.
	if (IsName(token))
	{
		fsm->setCurrent(new st1);
		type = tokenT::VARIABLE;
		delete this;
	}
	else
	{
		throw "Error: Mathematical expression must start with a name of variable to be assigned to";
	}
	return token;
}

std::string st1::processToken(fsmT* fsm, const std::string &token, tokenT::typeT &type)
{
	// After first variable in expression assignment operator is expected
	if (!token.compare("="))
	{
		fsm->setCurrent(new st2);
		type = tokenT::OPERATOR;
		delete this;
	}
	else
	{
		throw "Error: assignment operator expected";
	}
	return token;
}

std::string st2::processToken(fsmT* fsm, const std::string &token, tokenT::typeT &type)
{
	// Operand expected: name, constant, unary minus or opening parenthesis
	if (IsName(token))
	{
		fsm->setCurrent(new st3);
		type = tokenT::VARIABLE;
		delete this;
	}
	else if (IsNumber(token))
	{
		fsm->setCurrent(new st3);
		type = tokenT::CONSTANT;
		delete this;
	}
	else if (!token.compare("-"))
	{
		fsm->setCurrent(new st4);
		type = tokenT::OPERATOR;
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

std::string st3::processToken(fsmT* fsm, const std::string &token, tokenT::typeT &type)
{
	operatorInfoT* operatorInfo = &(operatorInfoT::Instance());
	std::string ops = operatorInfo->AllOperatorsAsString()/*("+-* /%^")*/;
	if (!token.compare(")"))
	{
		fsm->setCurrent(new st3);
		delete this;
	}
	else if (ops.find(token) != std::string::npos)
	{
		fsm->setCurrent(new st2);
		type = tokenT::OPERATOR;
		delete this;
	}
	else
	{
		throw "Error: Operation expected";
	}
	return token;
}

std::string st4::processToken(fsmT* fsm, const std::string &token, tokenT::typeT &type)
{
	if (IsName(token))
	{
		fsm->setCurrent(new st3);
		type = tokenT::VARIABLE;
		delete this;
	}
	else if (IsNumber(token))
	{
		fsm->setCurrent(new st3);
		type = tokenT::CONSTANT;
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

// Initialize interpreter's operator info
void FiniteStateMachine::InitializeOperatorInfo(parserT* interpreter) const
{
	interpreter->operatorInfo->AddOperator("+",  "+", operatorInfoT::PLUS, 6, operatorInfoT::LEFT, 2);
	interpreter->operatorInfo->AddOperator("-",  "-", operatorInfoT::MINUS, 6, operatorInfoT::LEFT, 2);
	interpreter->operatorInfo->AddOperator("u-", "-", operatorInfoT::UNARY_MINUS, 3, operatorInfoT::RIGHT, 1);
	interpreter->operatorInfo->AddOperator("*",  "*", operatorInfoT::TIMES, 5, operatorInfoT::LEFT, 2);
	interpreter->operatorInfo->AddOperator("/",  "/", operatorInfoT::DIVIDE, 5, operatorInfoT::LEFT, 2);
	interpreter->operatorInfo->AddOperator("%",  "%", operatorInfoT::MODULO, 5, operatorInfoT::LEFT, 2);
	interpreter->operatorInfo->AddOperator("^",  "^", operatorInfoT::POWER, 4, operatorInfoT::RIGHT, 2);
	interpreter->operatorInfo->AddOperator("=",  "=", operatorInfoT::ASSIGN, 15, operatorInfoT::RIGHT, 2);
}