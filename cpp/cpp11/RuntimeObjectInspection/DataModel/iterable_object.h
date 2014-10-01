#pragma once

#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>

#include "common.h"
#include "IObject.h"

class Object : public IObject
{
	container_t properties_;
	std::unordered_map<std::string, size_t> indexMap_;
public:
	Object(const std::string &name);
	~Object() override;

	container_t::const_iterator begin();
	container_t::const_iterator end();

	void add(IObject* value) override;

	std::string toString();
	container_t getProperties() override;

	template <class T>
	IObject &operator[](const T key);
};