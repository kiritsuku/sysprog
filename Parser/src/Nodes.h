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
    // Index, Exp2, Exp2Minus, Exp2Neg, StatementWrite, Statements
    explicit Node(NodeType tpe, Node *n1);
    // Prog, Decls, OpExp, Statements, StatementWhile
    explicit Node(NodeType tpe, Node *n1, Node *n2);
    // StatementIf
    explicit Node(NodeType tpe, Node *n1, Node *n2, Node *n3);
    // DeclIdent
    explicit Node(NodeType tpe, Symbol *symbol);
    // DeclArray, Exp2Ident, StatementRead
    explicit Node(NodeType tpe, Node *n1, Symbol *symbol);
    // StatementIdent
    explicit Node(NodeType tpe, Symbol *symbol, Node *n1, Node *n2);
    // Nil
    explicit Node(NodeType tpe);
    // Array, Exp2Int
    explicit Node(NodeType tpe, unsigned intValue);
    // Op
    explicit Node(NodeType tpe, Tokens::Token *token);

    ~Node();

    /** Always defined for all types */
    NodeType tpe();
    /** Only defined for: Decls */
    Node *decl();
    /** Only defined for: Prog */
    Node *decls();
    /** Only defined for: Statements, StatementWhile */
    Node *stmt();
    /** Only defined for: Prog */
    Node *stmts();
    /** Only defined for: Decls */
    Node *nextDecl();
    /** Only defined for: Statements */
    Node *nextStmt();
    /** Only defined for: DeclArray */
    Node *arr();
    /** Only defined for: StatementIdent, StatementWrite, StatementIf, StatementWhile, Exp2, Index, OpExp */
    Node *exp();
    /** Only defined for: Exp, Exp2Minus, Exp2Neg */
    Node *exp2();
    /** Only defined for: Exp, OpExp */
    Node *op();
    /** Only defined for: StatementIdent, StatementRead, Exp2Ident */
    Node *index();
    /** Only defined for: StatementIf */
    Node *ifStmt();
    /** Only defined for: StatementIf */
    Node *elseStmt();
    /** Only defined for: DeclArray, DeclIdent, StatementIdent, StatementRead, Exp2Ident */
    Symbol *symbol();
    /** Only defined for: Array, Exp2Int */
    unsigned intValue();
    /** Only defined for: Op */
    Tokens::Token *token();

    const char *tpeName();

  private:
    NodeType _tpe;
    Node *_n1;
    Node *_n2;
    Node *_n3;
    Symbol *_symbol;
    unsigned _intValue;
    Tokens::Token *_token;

    void err(const char *fnName);
  };
}
#endif
