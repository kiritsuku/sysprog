#include <string.h>
#include <stdlib.h>
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
  errors(new Error*[maxErrors])
{
  memset(errors, 0, sizeof(Error*)*maxErrors);
}

ErrorHandler::~ErrorHandler()
{
  for (unsigned i = 0; i < numberOfErrors; ++i) {
    auto e = errors[i];
    delete[] e->msg;
    delete e;
  }
  delete[] errors;
}

void ErrorHandler::addError(unsigned pos, const char *msg)
{
  if (numberOfErrors == maxErrors-1)
    resize();

  auto len = strlen(msg);
  auto buf = new char[len+1];
  strcpy(buf, msg);
  buf[len] = '\0';

  errors[numberOfErrors++] = new Error{pos, buf};
}

void ErrorHandler::resize()
{
  auto oldErrors = errors;
  auto oldMaxErrors = maxErrors;
  maxErrors *= 2;
  errors = new Error*[maxErrors];
  memset(errors, 0, sizeof(Error*)*maxErrors);
  memcpy(errors, oldErrors, sizeof(Error*)*oldMaxErrors);
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

int errorCmp(const void *a, const void *b)
{
  auto *e1 = (ErrorHandler::Error*) a;
  auto *e2 = (ErrorHandler::Error*) b;
  return e1->pos - e2->pos;
}

/**
 * @param buffer
 *        The buffer that is searched for line endings.
 * @param lineCounter
 *        Counts the number of lines that are already found. Will be
 *        incremented by this function every time a new line is found.
 * @parem lastLinePos
 *        The position of the last line ending.
 * @param end
 *        Denotes at which position to end the search for line endings.
 */
void findLine(char *buffer, unsigned *lineCounter, unsigned *lastLinePos, unsigned end)
{
  auto i = *lastLinePos+1;
  while (i < end) {
    if (buffer[i] == '\n') {
      *lastLinePos = i;
      ++(*lineCounter);
    }
    ++i;
  }
}

void ErrorHandler::showErrorMessages()
{
  if (hasErrors()) {
    char *content;
    auto size = readFile(&content, fileName);
    // the maximum size of the error message before and after
    // the errors  position
    auto partSize = 30;
    unsigned lineCount = 1;
    unsigned linePos = 0;

    qsort(errors, numberOfErrors, sizeof(Error*), errorCmp);

    for (unsigned i = 0; i < numberOfErrors; ++i) {
      auto error = errors[i];
      findLine(content, &lineCount, &linePos, error->pos);

      auto start = startPos(content, error->pos, partSize);
      auto end = endPos(content, size, error->pos, partSize);
      auto len = end-start;

      char line[len+1];
      strncpy(line, content+start, len);
      line[len] = 0;

      auto spaces = error->pos-start;
      auto column = error->pos-linePos+(lineCount == 1 ? 1 : 0);
      // we have to pass n+1 in order that %* prints n characters
      printf("\n%d,%d: error: %s\n\t%s\n\t%*c\n",
          lineCount, column, error->msg, line, spaces+1, '^');
    }

    delete[] content;
  }
}

bool ErrorHandler::hasErrors()
{
  return numberOfErrors > 0;
}
