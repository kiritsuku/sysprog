#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ErrorHandler.h"

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

/**
 * Find the start position of the error message.
 *
 * The minimum value that can be returned is `offset-partSize`.
 */
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

/**
 * Find the end position of the error message.
 *
 * The maximum value that can be returned is `offset+partSize`.
 *
 * `size` is the size of `buffer`.
 */
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

/**
 * Read the entire file `fileName` in memory.
 *
 * Returns the size of buf.
 */
unsigned ErrorHandler::readFile(char **buf)
{
  Buffer buffer(fileName);
  unsigned ALLOC = 1024;
  unsigned bufSize = ALLOC;
  auto b = new char[bufSize];
  unsigned i = 0;
  char c = buffer.currentChar();

  while (c != 0) {
    if (i >= bufSize-1) {
      auto tmp = new char[bufSize+ALLOC];
      strncpy(tmp, b, bufSize);
      bufSize += ALLOC;
      delete[] b;
      b = tmp;
    }
    b[i++] = c;
    c = buffer.nextChar();
  }

  b[i] = 0;
  *buf = b;
  return i;
}

void ErrorHandler::showErrorMessages()
{
  if (hasErrors()) {
    char *content;
    auto size = readFile(&content);
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
