#ifndef CODE_GEN_H_
#define CODE_GEN_H_

#include <sstream>
#include "Nodes.h"

class CodeGen final {
public:
  CodeGen();
  ~CodeGen();
  /** Generates code and stores it in `ss`. */
  void makeCode(std::stringstream &ss, Nodes::Node *node);

private:
  unsigned nrOfLabels;
  unsigned maxNrOfLabels;
  const char **labels;

  /** Creates a new unique label. */
  const char *mkLabel();
  void resize();
};
#endif
