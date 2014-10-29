#ifndef ERROR_HANDLER_H_
#define ERROR_HANDLER_H_

class ErrorHandler final {
public:
  ErrorHandler(const char *fileName);
  ~ErrorHandler();

  void addErrorPos(unsigned pos);
  void showErrorMessages();
  bool hasErrors();
private:
  const char *fileName;
  unsigned numberOfErrors;
  unsigned maxErrors;
  unsigned *errors;

  void resize();
};

#endif
