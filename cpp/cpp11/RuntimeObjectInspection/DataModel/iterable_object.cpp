#include "stdafx.h"
#include "iterable_object.h"


Object::Object(const std::string &name)
{
	name_ = name;
	type_ = "";
}


Object::~Object()
{
}

std::string Object::toString()
{
	return std::string("<Object>") + " [" + name_ + "]";
}

std::vector<IObject*> Object::getProperties()
{
	return value_;
}

std::vector<IObject*>::const_iterator Object::begin()
{
	return value_.begin();
}

std::vector<IObject*>::const_iterator Object::end()
{
	return value_.end();
}

void Object::push_back(IObject* value)
{
	value_.push_back(value);
}

IObject* Object::back()
{
	return value_.back();
}

IObject & Object::operator[](const std::string &key)
{
	for (auto &value : value_)
	{
		if (!key.compare(value->getName()))
		{
			return *value;
		}
	}
	throw std::string("Property \'") + key + std::string("\' not found");
}

