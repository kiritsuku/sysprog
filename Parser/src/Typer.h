#ifndef TYPER_H_
#define TYPER_H_

#include "Nodes.h"

class Typer final {
public:
  void typeCheck(Nodes::Node *node);

private:
  void err(const char *msg);
};

#endif
