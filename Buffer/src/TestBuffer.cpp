#include <stdio.h>
#include "Buffer.h"


int main()
{
  const char name[] = "/home/antoras/xxx";
	Buffer buffer{name};

  buffer.nextChar();

  printf("hello\n");
}
