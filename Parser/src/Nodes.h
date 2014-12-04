#ifndef NODES_H_
#define NODES_H_

#include "Symboltable.h"

namespace Nodes {

  enum NodeType {
    Prog,
    Decls,
    DeclArray,
    DeclIdent,
    Array,
    Nil,
  };

  class Node final {
  public:
    // Prog
    Node(NodeType _tpe, Node *_decls, Node *_stmts);
    // Decls
    Node(NodeType _tpe, Node *_nextDecl);
    // DeclArray
    Node(NodeType _tpe, Node *_arr, Symbol *_name);
    // DeclIdent
    Node(NodeType _tpe, Symbol *_name);
    // Array
    Node(NodeType _tpe, unsigned _size);
    // Nil
    Node(NodeType _tpe);

    NodeType tpe();
    Node *decls();
    Node *stmts();
    Node *nextDecl();
    Node *arr();
    Symbol *name();
    unsigned size();

  private:
    NodeType _tpe;
    Node *_decls;
    Node *_stmts;
    Node *_nextDecl;
    Node *_arr;
    Symbol *_name;
    unsigned _size;
  };
}
#endif
