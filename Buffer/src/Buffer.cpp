#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include "Buffer.h"

Buffer::Buffer(const char *const fileName):
  fileName(fileName),
  curBuffer(),
  off(0)
{
  fillBuffer();
}

Buffer::~Buffer()
{
}

void printErr(const char* format, ...)
{
  // http://stackoverflow.com/questions/1056411/how-to-pass-variable-number-of-arguments-to-printf-sprintf
  va_list argptr;
  va_start(argptr, format);
  vfprintf(stderr, format, argptr);
  va_end(argptr);
  fprintf(stderr, ": %s\n", strerror(errno));
}

FILE* openFileReadOnly(const char* name)
{
  FILE* f = nullptr;
  if ((f = fopen(name, "r")) == nullptr) {
    printErr("Could not open '%s'", name);
  }
  return f;
}

int fileSize(FILE* f)
{
  if (f == nullptr)
    return 0;

  fseek(f, 0, SEEK_END);
  int fileSize = ftell(f);
  rewind(f);
  return fileSize;
}

void Buffer::readFile(const char* name)
{
  char* buffer = this->curBuffer;
  FILE* f = nullptr;
  if ((f = openFileReadOnly(name)) != nullptr) {
    int size = fileSize(f);
    printf("file size: %d\n", size);
    for (int i = 0; i < size; i += BUFFER_SIZE) {
      int numRead = fread(buffer, 1, BUFFER_SIZE, f);
      if (numRead < 1) {
        printErr("Could not read from file '%s'", name);
        break;
      }
      // handles end of file
//      if (numRead < BUFFER_SIZE) {
//        memset(&buffer[numRead], 0, BUFFER_SIZE-numRead);
//      }
      printf(">>>%.*s<<<\n", numRead, buffer);
    }
    fclose(f);
  }
}

char Buffer::nextChar()
{
  off += 1;
  auto next = off < BUFFER_SIZE ? curBuffer[off] : 0;
  return next;
}
char Buffer::currentChar()
{
  return curBuffer[off];
}

unsigned Buffer::offset()
{
  return off;
}

char* Buffer::range(char *buffer, const unsigned start, const unsigned len)
{
  strncpy(buffer, curBuffer+start, len);
  buffer[len] = '\0';
  return buffer;
}

void Buffer::setOffset(const unsigned offset)
{
  off = offset;
}

void Buffer::fillBuffer()
{
  memset(curBuffer, 0, BUFFER_SIZE);
  strcpy(curBuffer, "hello \n\nworld\n100+1*235761:=556<:>hel22lo=598");
  //readFile(this->fileName);
}
