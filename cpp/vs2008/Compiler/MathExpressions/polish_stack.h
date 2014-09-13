#pragma once

#include <cstdio>
#include <map>
#include <stack>
#include <string>

#include "token.h"

// T - type of word name
template<class T>
class polishStackT : public std::stack<T>
{
private:
    std::map<std::string, int> dict;
public:
	using std::stack<T>::push;
	void push(const T &token, int val)
	{
		std::stack<T>::push(token);
	}

	int topVal() const
	{
		return this->top()->getValue(this->dict);
	}
	
	std::string topName() const
	{
		return this->top()->getName();
	}

	void DictInsert(const std::string &word, int val)
	{
		dict.insert(std::pair<std::string, int>(word, val));
	}

	void DictUpdate(const std::string &word, int val)
	{
		dict[word] = val;
	}

	int DictFind(const std::string &word) const
	{
		typename std::map<T, int>::const_iterator wordCard = dict.find(word);
		if (wordCard == dict.end())
		{
			throw "Error: word not found";
		}
		else
		{
			return wordCard->second;
		}
	}
};
