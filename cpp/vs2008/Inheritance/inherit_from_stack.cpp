#include <cstdio>
#include <map>
#include <stack>
#include <string>

// T - type of word name
// D - type of its description
template<class T, class D>
class polishStackT : public std::stack<T>
{
private:
    std::map<T, D> dict;
public:
    //using std::stack<T>::push;
    void push(const T &name, D val)
    {
	std::stack<T>::push(name);
	this->DictInsert(name, val);
    }

    D topVal() const
    {
	return this->DictFind(this->top());
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

int main(void)
{
    polishStackT<std::string, int> ps;
    ps.push("one", 1);
    ps.push("two", 2);
    ps.push("three", 33);
    ps.push("five", 5);
    ps.DictUpdate("three", 3);

    while (!ps.empty())
    {
	printf("%s - %d\n", ps.top().c_str(), ps.topVal());
	ps.pop();
    }
    return 0;
}
