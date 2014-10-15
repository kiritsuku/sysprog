#ifndef BUFFER_H_
#define BUFFER_H_

class Buffer {
private:
  const char* fileName;
  //char* curBuffer;
  //char* prevBuffer;
public:
	explicit Buffer(const char* fileName): fileName(fileName) {}
  ~Buffer() {}

  virtual char nextChar();
  virtual int offset();
  virtual char* region(const unsigned int offset);
};

#endif /* BUFFER_H_ */
