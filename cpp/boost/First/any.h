#pragma once

#include <list>
#include <string>
#include <boost/any.hpp>

using boost::any_cast;
typedef std::list<boost::any> many;

void append_int(many & values, int value)
{
	boost::any to_append = value;
	values.push_back(to_append);
}

void append_string(many & values, const std::string & value)
{
	values.push_back(value);
}

void append_char_ptr(many & values, const char * value)
{
	values.push_back(value);
}

void append_any(many & values, const boost::any & value)
{
	values.push_back(value);
}

void append_nothing(many & values)
{
	values.push_back(boost::any());
}

void main_any()
{
	many ls;
	append_int(ls, 3);
	append_string(ls, std::string("three"));

	BOOST_FOREACH(boost::any v, ls)
	{
		int x = 2;
		std::cout << any_cast<int>(v) << std::endl;
	}
}