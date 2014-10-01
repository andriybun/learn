#include "stdafx.h"
#include "common.h"

template<> std::string getTypeName<int>()
{
	return std::string("int");
}

template<> std::string getTypeName<std::string>()
{
	return std::string("std::string");
}

template<> std::string convertToString<std::string>(const std::string &val)
{
	return val;
}

template<> std::string convertToString<int>(const int &val)
{
	return  std::to_string(val);
}