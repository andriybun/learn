#include <cstdio>
#include <map>
#include <stack>
#include <string>

#include "token.h"

// T - type of word name
// D - type of its description
template<class T, class D>
class polishStackT : public std::stack<T>
{
private:
    std::map<T, D> dict;
public:
    using std::stack<T>::push;
    void push(const T &name, D val)
    {
	std::stack<T>::push(name);
	this->DictInsert(name, val);
    }

    D topVal() const
    {
	return this->top().getValue(this->dict);
    }

    void DictInsert(const T &word, D val)
    {
	dict.insert(std::pair<T, D>(word, val));
    }

    void DictUpdate(const T &word, D val)
    {
	dict[word] = val;
    }

    D DictFind(const T &word) const
    {
	typename std::map<T, D>::const_iterator wordCard = dict.find(word);
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
