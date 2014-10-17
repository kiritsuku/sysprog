#ifndef BUFFER_H_
#define BUFFER_H_

static const unsigned BUFFER_SIZE = 16;

class Buffer {
private:
  const char* fileName;
  char curBuffer[BUFFER_SIZE];
  //char* prevBuffer;
  unsigned off;
public:
	explicit Buffer(const char* fileName): fileName(fileName), curBuffer(), off(0) {}
  ~Buffer() {}

  virtual char nextChar();
  virtual int offset();
  virtual char* region(const unsigned int offset);
private:
  virtual void readFile(const char* name);
};

#endif /* BUFFER_H_ */
