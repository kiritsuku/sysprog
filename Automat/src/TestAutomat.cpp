#include <stdio.h>
#include "Automat.h"
#include "Token.h"

Tokens::Token *f()
{
  return Tokens::None;
}

int main()
{
  Tokens::Token *t = Tokens::SmallerColonGreater;
  printf("eq: %d\n", Tokens::None == f());
  printf("eq: %d\n", t == Tokens::SmallerColonGreater);
  printf("text: %s\n", t->text());
  auto len = t->textLen();
  printf("len: %d\n", len);
  return 0;
}
