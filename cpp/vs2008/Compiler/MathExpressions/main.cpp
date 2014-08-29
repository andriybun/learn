#include <string>
#include "parser.h"

using namespace std;

int main(int argc, char **argv)
{
	string inp("a + bad * c45a / (24 + de)");
	//string inp("a = 3 + 4 * 2 / (1 - 5) ^ 2 ^ 3");
	// TODO: power operator right assoc..
	parserT parse;
	try
	{
		parse.AddVariable("a", 13);
		parse.AddVariable("bad", 33);
		parse.AddVariable("c45a", 42);
		parse.AddVariable("de", 76);
		parse.EvaluateExpression(inp);
		//parse.EvaluateExpression("a = 3 + 4 * 2 / (1 - 5) ^ 2 ^ 3");
	}
	catch (const char * e)
	{
		printf("Exception: %s\n", e);
	}
	
	
	

	return 0;
}