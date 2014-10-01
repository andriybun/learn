#pragma once

#include <string>
#include <vector>

class IObject
{
protected:
	std::string name_, type_;
	std::vector<IObject*> properties_;
public:
	virtual ~IObject() {};
	std::string getName() { return name_; };
	std::string getType() { return type_; };
	virtual std::string toString() = 0;
	IObject* getValue() { return this; };
	virtual std::vector<IObject*> getProperties() { return properties_; };

	virtual IObject &operator[](const std::string &key)
    { 
		if (!key.compare(name_)) return *this;
		throw std::string("Property \'") + key + std::string("\' not found");
    };
};
