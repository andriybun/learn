#include <string>
#include "parser.h"

using namespace std;

int main(int argc, char **argv)
{
	parserT parse;
	try
	{
		parse.EvaluateExpression("a = 13");
		parse.EvaluateExpression("bad = 33");
		parse.EvaluateExpression("c45a = 42");
		parse.EvaluateExpression("de = 76");
		parse.EvaluateExpression("b = a + bad * c45a / (24 + (de))");
		parse.EvaluateExpression("a = b + 3 + 4 * 8 / (1 - 5) ^ 2");
	}
	catch (const char * e)
	{
		printf("Exception: %s\n", e);
	}

	return 0;
}
