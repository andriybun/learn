#pragma once

#include <string>
#include <vector>

class IObject;
typedef std::vector<IObject*> container_t;

class IObject
{
protected:
	std::string name_, type_;
	container_t properties_;
public:
	virtual ~IObject() {};
	std::string getName() { return name_; };
	std::string getType() { return type_; };
	IObject* getValue() { return this; };
	virtual std::string toString() = 0;
	virtual void add(IObject* value)
	{
		throw std::string("add() not possible");
	};
	virtual container_t getProperties() { return properties_; };

	template <class T>
	IObject &operator[](const T key)
    { 
		throw std::string("operator [] not implemented for this type of object");
    };
};
