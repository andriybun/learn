#include "parser.h"

bool operation(const std::string &s)
{
    size_t pos = 0;
    while ((pos < s.length()) && expression(s, pos))
    {
	if (s[pos++] != ';')
	{
	    std::printf("%zu - \';\' expected\n", pos-1);
	    return false;
	}
    }
    return (pos == s.length());
}

bool expression(const std::string &s, size_t &pos)
{
    size_t posBackup = pos;
    if (!s.compare(pos, 4, "for "))
    {
	return loop(s, pos);
    }
    if (equation(s, pos)) 
    {
	return true;
    }
    return false;
}

bool loop(const std::string &s, size_t &pos)
{
    size_t posBackup = pos;
    if (!loopHeader(s, pos))
    {
	std::printf("%zu - error in for loop header\n", posBackup);
	return false;
    }
    if (s[pos++] != '{')
    {
	std::printf("%zu - for loop header must be followed by \'{\'\n", pos-1);
	return false;
    }
    if (s[pos] == '}')
    {
	pos++;
	return true;
    }
    posBackup = pos;
    if (!equation(s, pos))
    {
	std::printf("%zu - error in for loop body\n", pos-1);
	return false;
    }
    if (s[pos++] != '}')
    {
	std::printf("%zu - for loop body must be followed by \'}\'\n", pos-1);
	return false;
    }
    return true;
}

bool loopHeader(const std::string &s, size_t &pos)
{
    bool isFor = !s.compare(pos, 4, "for ");
    pos += 4;
    bool isLoopVar = identifier(s, pos);
    bool isAssignment = (s[pos++] == '=');
    bool isLowerBound = term(s, pos);
    bool isColon = (s[pos++] == ':');
    bool isUpperBound = term(s, pos);
    return (isFor && isLoopVar && isAssignment && isLowerBound && isColon && isUpperBound);
}

bool term(const std::string &s, size_t &pos)
{
    size_t posBackup = pos;
    if (isalpha(s[pos]))
    {
	bool isName = identifier(s, pos);
	if (isName)
	{
	    return true;
	}
	std::printf("%zu - not a valid variable/function name", posBackup);
	return false;
    }
    if (isdigit(s[pos]))
    {
	bool isConstant = constant(s, pos);
	if (isConstant)
	{
	    return true;
	}
	std::printf("%zu - not a valid constant\n", posBackup);
	return false;
    }
    std::printf("%zu - valid constant or variable name expected\n", posBackup);
    return false;
}

bool constant(const std::string &s, size_t &pos)
{
    while (isdigit(s[pos])) {pos++;};
    return !(isalpha(s[pos]) || (s[pos] == '_'));
}

bool validIdentifierCharacter(const std::string &s, size_t &pos)
{
    if (isalpha(s[pos]) || isdigit(s[pos]) || (s[pos] == '_'))
    {
	return true;
    }
    return false;
}

bool identifier(const std::string &s, size_t &pos)
{
    if (isalpha(s[pos++]))
    {
	while(validIdentifierCharacter(s, pos)) pos++;
    }
    return true;
}

bool functionParameters(const std::string &s, size_t &pos)
{
    size_t posBackup = pos;
    size_t errorPos = 0;
    char errorIdx = 0;
    if (s[pos++] != '(') 
    {
	errorPos = pos-1;
	errorIdx = 1;
    }
    if (s[pos] == ')')
    {
	pos++;
	return true;
    }
    else
    {
	if (!term(s, pos))
	{
	    std::printf("%zu - incorrect function parameter\n", posBackup);
	    return false;
	}
	while (s[pos] == ',')
	{
	    if (!term(s, ++pos))
	    {
		std::printf("%zu - incorrect function parameter\n", posBackup);
		return false;
	    }
	}
    	if (s[pos++] != ')') 
	{
	    errorPos = pos-1;
	    errorIdx = 2;
	}
    }
    switch (errorIdx)
    {
    case 0:
	return true;
	break;
    case 1:
	std::printf("%zu - \'(\' expected before function parameter list\n", errorPos);
	return false;
	break;
    case 2:
	std::printf("%zu - \')\' expected after function parameter list\n", errorPos);
	return false;
	break;
    }
    return true;
}

bool equation(const std::string &s, size_t &pos)
{
    size_t posBackup = pos;
// printf("%zu: equation\n", pos);
    bool isName = identifier(s, pos);
    if (!isName)
    {
	std::printf("%zu - incorrect mathematical expression\n", posBackup);
	return false;
    }
    bool isAssignment = (s[pos] == '=');
    bool isFunctionCall = (s[pos] == '(');
    if (isAssignment)
    {
	return math(s, ++pos);
    }
    if (isFunctionCall)
    {
	return functionParameters(s, pos);
    }
    return false;
}

bool math(const std::string &s, size_t &pos)
{
    size_t posBackup = pos;
    if (s[pos] == '-')
    {
	pos++;
	return math(s, pos);
    }
    if (s[pos] == '(')
    {
	pos++;
	math(s, pos);
	if (s[pos++] != ')')
	{
	    std::printf("%zu - \')\' expected\n", pos-1);
	    return false;
	}
    }
    else if (!term(s, pos))
    {
	return false;
    }
    if (s[pos] == '(')
    {
	functionParameters(s, pos);
    }
    if (oper(s, pos))
    {
	return math(s, pos);
    }
    else
    {
	pos--;
    }
    return true;
}

bool oper(const std::string &s, size_t &pos)
{
    size_t found = legalOperatorList.find(s[pos++]);
    return (found != std::string::npos);
}
