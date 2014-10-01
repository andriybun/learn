#pragma once

#include <string>
#include <vector>

#include "common.h"
#include "IObject.h"
#include "album.h"
#include "track.h"

template <class T>
class ValueObject : public IObject
{
	T value_;
public:
	ValueObject(const std::string &name, const T &value);
	~ValueObject() override;
	std::string toString() override;
};
