#include <stdio.h>
#include <string.h>
#include "Symboltable.h"

int main()
{
	Symboltable st;

  auto str1 = "hello";
  auto str2 = "world";
  auto str3 = "hello";
  auto sym1 = st.create((char*) str1);
  auto sym2 = st.create((char*) str2);
  auto sym3 = st.create((char*) str3);

  printf("sym1: %s\n", sym1->ident);
  printf("sym2: %s\n", sym2->ident);
  printf("sym3: %s\n", sym3->ident);
  printf("%d\n", sym1 == sym3);
  return 0;
}
