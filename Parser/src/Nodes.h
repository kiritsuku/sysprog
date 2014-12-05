#ifndef NODES_H_
#define NODES_H_

#include "Token.h"
#include "Symboltable.h"

namespace Nodes {

  enum NodeType {
    Prog,
    Decls,
    DeclArray,
    DeclIdent,
    Array,
    Statements,
    StatementIdent,
    StatementWrite,
    StatementRead,
    StatementBlock,
    StatementIf,
    StatementWhile,
    Exp,
    Exp2,
    Exp2Ident,
    Exp2Int,
    Exp2Minus,
    Exp2Neg,
    Index,
    OpExp,
    Op,
    Nil,
  };

  class Node final {
  public:
    // Prog, Decls, OpExp, Statements
    explicit Node(NodeType _tpe, Node *_decls, Node *_stmts);
    // Index, Exp2, Exp2Minus, Exp2Neg, StatementWrite, Statements
    explicit Node(NodeType _tpe, Node *_nextDecl);
    // DeclArray, Exp2Ident, StatementRead
    explicit Node(NodeType _tpe, Node *_arr, Symbol *_name);
    // DeclIdent
    explicit Node(NodeType _tpe, Symbol *_name);
    // Array, Exp2Int
    explicit Node(NodeType _tpe, unsigned _size);
    // Nil
    explicit Node(NodeType _tpe);
    // Op
    explicit Node(NodeType _tpe, Tokens::Token *_token);
    // StatementIdent
    explicit Node(NodeType _tpe, Symbol *_ident, Node *_idx, Node *_exp);
    // StatementIf
    explicit Node(NodeType _tpe, Node *_exp, Node *_ifStmt, Node *_elseStmt);

    ~Node();

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
    Tokens::Token *_token;
  };
}
#endif
