#include "Parser.h"

Parser::Parser(Scanner &scanner, ErrorHandler &handler):
  scanner(scanner),
  handler(handler)
{
}

Parser::~Parser()
{
}
