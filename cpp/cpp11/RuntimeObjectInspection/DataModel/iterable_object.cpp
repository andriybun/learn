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

container_t Object::getProperties()
{
	return properties_;
}

container_t::const_iterator Object::begin()
{
	return properties_.begin();
}

container_t::const_iterator Object::end()
{
	return properties_.end();
}

void Object::add(IObject* value)
{
	std::string name = value->getName();
	auto search = indexMap_.find(name);
	if (search == indexMap_.end())
	{
		indexMap_[name] = properties_.size();
	}
	properties_.push_back(value);
}

template <>
IObject & Object::operator[](const std::string &key)
{
	auto search = indexMap_.find(key);
	if (search != indexMap_.end()) return *properties_[search->second];
	throw std::string("Property \'") + key + std::string("\' not found");
}

template <>
IObject & Object::operator[](const char* const key)
{
	auto search = indexMap_.find(key);
	if (search != indexMap_.end()) return *properties_[search->second];
	throw std::string("Property \'") + key + std::string("\' not found");
}

template <>
IObject & Object::operator[](const int &key)
{
	return *properties_[key];
}
