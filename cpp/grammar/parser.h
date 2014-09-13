#pragma once

#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>

const std::string legalOperatorList("+-*/^%");

bool operation(const std::string &s);
bool expression(const std::string &s, size_t &pos);
bool loop(const std::string &s, size_t &pos);
bool loopHeader(const std::string &s, size_t &pos);
bool term(const std::string &s, size_t &pos);
bool constant(const std::string &s, size_t &pos);
bool identifier(const std::string &s, size_t &pos);
bool functionParameters(const std::string &s, size_t &pos);
bool equation(const std::string &s, size_t &pos);
bool math(const std::string &s, size_t &pos);
bool oper(const std::string &s, size_t &pos);
