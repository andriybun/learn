#pragma once

#include <cstdio>
#include <map>
#include <stack>
#include <string>

class WorkspaceVariables;

// T - type of word name
template<class T>
class polishStackT : public std::stack<T>
{
public:
	using std::stack<T>::push;
	void push(const T &token, int val)
	{
		std::stack<T>::push(token);
	}

	int topVal(const WorkspaceVariables &dict) const
	{
		return this->top()->getValue(dict);
	}
	
	std::string topName() const
	{
		return this->top()->getName();
	}
};
