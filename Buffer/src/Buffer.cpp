#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include "Buffer.h"

static void printErr(const char* format, ...)
{
  // http://stackoverflow.com/questions/1056411/how-to-pass-variable-number-of-arguments-to-printf-sprintf
  va_list argptr;
  va_start(argptr, format);
  vfprintf(stderr, format, argptr);
  va_end(argptr);
  fprintf(stderr, ": %s\n", strerror(errno));
}

static int openFileReadOnly(const char* name)
{
  int fd;
  if ((fd = open(name, O_RDONLY | O_DIRECT)) < 0) {
    printErr("Could not open '%s'", name);
  }
  return fd;
}

/**
 * Allocates memory of `alignLen` size and aligns it by `alignLen`.
 */
static void mem(char **buf, unsigned alignLen)
{
  int err = posix_memalign((void **)buf, alignLen, alignLen);
  if (err != 0) {
    errno = err;
    printErr("Could not allocate memory");
  }
}

unsigned const Buffer::BUFFER_SIZE = 2048;

Buffer::Buffer(const char *const fileName):
  fileName(fileName),
  prevBuffer(nullptr),
  curBuffer(nullptr),
  off(0),
  offInFile(0),
  eofReached(false),
  fileDescriptor(0)
{
  mem(&curBuffer, BUFFER_SIZE);
  mem(&prevBuffer, BUFFER_SIZE);
  readNext();
}

Buffer::~Buffer()
{
  if (fileDescriptor > 0 && close(fileDescriptor) < 0)
    printErr("Could not close file '%s'", fileName);
  if (prevBuffer != nullptr)
    delete prevBuffer;
  if (curBuffer != nullptr)
    delete curBuffer;
}

void Buffer::readNext()
{
  if (eofReached)
    return;
  if (fileDescriptor == 0)
    fileDescriptor = openFileReadOnly(fileName);
  if (fileDescriptor < 0) {
    eofReached = true;
    return;
  }

  // swap buffer pointer
  auto tmp = prevBuffer;
  prevBuffer = curBuffer;
  curBuffer = tmp;

  // read data from file
  errno = 0;
  int sizeRead = read(fileDescriptor, curBuffer, BUFFER_SIZE);
  if (sizeRead == (int) BUFFER_SIZE) {
    offInFile += sizeRead;
  }
  else {
    eofReached = true;
    if (sizeRead < 0)
      printErr("Could not read from file '%s'", fileName);
    else
      offInFile += sizeRead;
  }
}

char Buffer::nextChar()
{
  off += 1;
  if (off >= offInFile)
    readNext();

  return currentChar();
}

char Buffer::currentChar()
{
  return curBuffer[off%BUFFER_SIZE];
}

unsigned Buffer::offset()
{
  return off;
}

char* Buffer::range(char *buffer, const unsigned start, const unsigned len)
{
  auto bufEnd = offInFile%BUFFER_SIZE == 0 ? offInFile-BUFFER_SIZE : offInFile-(offInFile%BUFFER_SIZE);

  // we can copy onyly from the last buffer
  if (start > bufEnd)
    strncpy(buffer, this->curBuffer+start, len);
  // we also need to copy from the previous buffer
  else {
    auto readPrev = bufEnd-start;
    strncpy(buffer, prevBuffer+BUFFER_SIZE-readPrev, readPrev);
    strncpy(buffer+readPrev, curBuffer, len-readPrev);
  }
  buffer[len] = 0;
  return buffer;
}

void Buffer::setOffset(const unsigned offset)
{
  off = offset;
}
