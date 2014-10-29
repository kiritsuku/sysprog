#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <math.h>
#include "ErrorHandler.h"

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

unsigned readFile(char **buffer, const char *name)
{
  FILE* f = nullptr;
  if ((f = openFileReadOnly(name)) != nullptr) {
    auto bufferSize = fileSize(f);
    auto buf = new char[bufferSize];
    int numRead = fread(buf, 1, bufferSize, f);
    if (numRead < 1 && ferror(f) != 0) {
      printErr("Could not read from file '%s'", name);
    }
    fclose(f);
    *buffer = buf;
    return bufferSize;
  }
  return 0;
}

ErrorHandler::ErrorHandler(const char *fileName):
  fileName(fileName),
  numberOfErrors(0),
  maxErrors(10),
  errors(new unsigned[maxErrors])
{
}

ErrorHandler::~ErrorHandler()
{
  delete[] errors;
}

void ErrorHandler::addErrorPos(unsigned pos)
{
  if (numberOfErrors == maxErrors-1)
    resize();

  errors[numberOfErrors++] = pos;
}

void ErrorHandler::resize()
{
  auto oldErrors = errors;
  auto oldMaxErrors = maxErrors;
  maxErrors *= 2;
  errors = new unsigned[maxErrors];
  memcpy(errors, oldErrors, sizeof(unsigned)*oldMaxErrors);
  delete[] oldErrors;
}

unsigned startPos(char *buffer, unsigned offset, unsigned partSize)
{
  if (buffer[offset] == '\n')
    return offset;

  unsigned start = offset;
  unsigned readMax = fmax((int)offset-(int)partSize, 0);
  while (start > readMax && buffer[start] != '\n')
    --start;
  return buffer[start] != '\n' ? start : start+1;
}

unsigned endPos(char *buffer, unsigned size, unsigned offset, unsigned partSize)
{
  if (size <= 0)
    return 0;
  if (offset >= size)
    return size;
  if (buffer[offset] == '\n')
    return offset;

  unsigned end = offset;
  unsigned readMax = fmin((int)offset+(int)partSize, size-1);
  while (end < readMax && buffer[end] != '\n')
    ++end;
  return end;
}

void ErrorHandler::showErrorMessages()
{
  if (hasErrors()) {
    char *content;
    auto size = readFile(&content, fileName);
    auto partSize = 30;

    for (unsigned i = 0; i < numberOfErrors; ++i) {
      auto offset = errors[i];
      auto start = startPos(content, offset, partSize);
      auto end = endPos(content, size, offset, partSize);
      auto len = end-start;


      char line[len+1];
      strncpy(line, content+start, len);
      line[len] = 0;

      auto spaces = offset-start;
      // we have to pass n+1 in order that %* prints n characters
      printf("\nline(%d),column(%d): error:\n\t%s\n\t%*c\n",
          0, offset, line, spaces+1, '^');
    }

    delete[] content;
  }
}

bool ErrorHandler::hasErrors()
{
  return numberOfErrors > 0;
}
