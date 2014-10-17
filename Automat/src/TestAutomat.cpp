#include <stdio.h>
#include "Automat.h"
#include "Token.h"

//int main(int argc, char* argv[])
int main()
{
	//Automat* automat;

  Tokens::Token t = Tokens::Ignore;
  printf("%d\n", t);
  auto len = Tokens::instance().textLen(Tokens::SmallerColonGreater);
  printf("len: %d\n", len);
  return 0;
}
