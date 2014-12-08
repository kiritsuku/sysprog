#ifndef TEST_HELPER_H_
#define TEST_HELPER_H_

#include <sstream>
#include <stdio.h>
#include <string.h>
#include "Scanner.h"
#include "Automat.h"
#include "Buffer.h"
#include "Token.h"
#include "Symboltable.h"
#include "ErrorHandler.h"
#include "Parser.h"
#include "Nodes.h"
#include "Typer.h"

void mkNesting(std::stringstream &ss, unsigned nesting);

void mkString(std::stringstream &ss, Nodes::Node *node, unsigned nesting);

void executeTest(Parser &parser);


#endif
