#pragma once

#include<iostream>
#include<string>
#include<vector>

#include "common.h"
#include "IObject.h"

class Object : public IObject
{
	std::vector<IObject*> value_;
public:
	Object(const std::string &name);
	~Object() override;

	std::vector<IObject*>::const_iterator begin();
	std::vector<IObject*>::const_iterator end();

	void push_back(IObject* value);
	IObject* back();

	std::string toString();
	std::vector<IObject*> getProperties() override;
	IObject &operator[](const std::string &key) override;
};