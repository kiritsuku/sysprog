#ifndef BUFFER_H_
#define BUFFER_H_

class Buffer final {
public:
	explicit Buffer(const char *const fileName);
  ~Buffer();

  /** Returns the next character */
  char nextChar();

  /**
   * Returns the character that is returned by `nextChar` the last time it
   * was called.
   */
  char currentChar();

  unsigned currentLine();

  unsigned currentColumn();

  /**
   * Returns the position of the current current character. In other words
   * it returns the number of characters that have already been read.
   */
  unsigned offset();

  /**
   * Fills `buffer` by the range of characters between `offset` and
   * `offset+len`.
   *
   * Returns the pointer to `buffer`.
   */
  char* range(char *buffer, const unsigned offset, const unsigned len);

  /**
   * Sets the offset to a different value.
   */
  void setOffset(const unsigned offset);

private:
  static unsigned const BUFFER_SIZE;

  const char *const fileName;
  char *prevBuffer;
  char *curBuffer;
  unsigned off;
  unsigned offInFile;
  bool eofReached;
  int fileDescriptor;
  char lastChar;
  unsigned line;
  unsigned column;

  void readNext();
};

#endif
