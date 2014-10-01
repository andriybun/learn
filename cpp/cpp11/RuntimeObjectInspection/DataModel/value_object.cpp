#include "stdafx.h"
#include "value_object.h"

///////////////////////////
// String object class
///////////////////////////

template<class T>
ValueObject<T>::ValueObject(const std::string &name, const T &value)
{
	name_ = name;
	value_ = value;
	type_ = getTypeName<T>();
}

template<class T>
ValueObject<T>::~ValueObject()
{

}

template<class T>
std::string ValueObject<T>::toString()
{
	return convertToString<T>(value_);
}

template class ValueObject < std::string > ;
template class ValueObject < int > ;
