#include <stdio.h>
#include "Buffer.h"


int main(int argc, char **argv)
{
  const char name[] = "/home/antoras/xxx";
	Buffer buffer{name};

  buffer.nextChar();

  printf("hello\n");
}
