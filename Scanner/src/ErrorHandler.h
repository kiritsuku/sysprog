#ifndef ERROR_HANDLER_H_
#define ERROR_HANDLER_H_

#include "Buffer.h"

class ErrorHandler final {
public:
  /**
   * `fileName` is the name of the file the errors belong to.
   */
  ErrorHandler(const char *fileName);
  ~ErrorHandler();

  /**
   * Logs an error message with a corresponding position.
   */
  void addError(unsigned pos, const char *msg);

  /**
   * Prints all error messages to stdout.
   */
  void showErrorMessages();

  /**
   * Returns `true` if `addError` has already been called.
   */
  bool hasErrors();

private:
  struct Error {
    const unsigned pos;
    const char *const msg;
  };
  const char *fileName;
  unsigned numberOfErrors;
  unsigned maxErrors;
  Error **errors;

  unsigned readFile(char **buf);
  /** Resizes `errors` if it is too small. */
  void resize();
  /** Used to sort `errors`. */
  friend int errorCmp(const void *a, const void *b);
};

#endif
