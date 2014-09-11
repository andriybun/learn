#include <iostream>
#include <cstdio>
#include <string>
#include "parser.h"

int main(int argc, char *argv[])
{
    std::string s(argv[1]);
    std::cout << "Processing string: \'" << s << "\'" << std::endl;
    for (size_t i = 0; i < s.length(); i++)
    {
	std::printf("%zu - %c\n", i, s[i]);
    }
    bool result = operation(s);
    std::cout << result << std::endl;
    return 0;
}
