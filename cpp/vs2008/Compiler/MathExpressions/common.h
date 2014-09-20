#pragma once

#include <locale>
#include <string>

inline bool IsNumber(const std::string &word)
{
	// TODO: allow floats
	std::string::const_iterator it = word.begin();
	std::locale loc;
	while (it != word.end() && std::isdigit(*it, loc)) ++it;
	return !word.empty() && it == word.end();
}

inline bool IsName(const std::string &word)
{
	std::string::const_iterator it = word.begin();
	std::locale loc;
	if (!std::isalpha(*it++, loc)) return false;
	while (it != word.end() && (std::isalpha(*it, loc) || std::isdigit(*it, loc))) ++it;
	return !word.empty() && it == word.end();
}
