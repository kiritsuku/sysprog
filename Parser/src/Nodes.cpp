#include <stdio.h>
#include <stdlib.h>
#include "Nodes.h"

using namespace Nodes;

Node::Node(NodeType tpe, Node *n1):
  _tpe(tpe),
  _type(Type::NoType),
  _n1(n1),
  _n2(nullptr),
  _n3(nullptr),
  _symbol(nullptr),
  _intValue(0),
  _token(nullptr)
{
}

Node::Node(NodeType tpe, Node *n1, Node *n2):
  _tpe(tpe),
  _type(Type::NoType),
  _n1(n1),
  _n2(n2),
  _n3(nullptr),
  _symbol(nullptr),
  _intValue(0),
  _token(nullptr)
{
}

Node::Node(NodeType tpe, Node *n1, Node *n2, Node *n3):
  _tpe(tpe),
  _type(Type::NoType),
  _n1(n1),
  _n2(n2),
  _n3(n3),
  _symbol(nullptr),
  _intValue(0),
  _token(nullptr)
{
}

Node::Node(NodeType tpe, Symbol *symbol):
  _tpe(tpe),
  _type(Type::NoType),
  _n1(nullptr),
  _n2(nullptr),
  _n3(nullptr),
  _symbol(symbol),
  _intValue(0),
  _token(nullptr)
{
}

Node::Node(NodeType tpe, Node *n1, Symbol *symbol):
  _tpe(tpe),
  _type(Type::NoType),
  _n1(n1),
  _n2(nullptr),
  _n3(nullptr),
  _symbol(symbol),
  _intValue(0),
  _token(nullptr)
{
}

Node::Node(NodeType tpe, Symbol *symbol, Node *n1, Node *n2):
  _tpe(tpe),
  _type(Type::NoType),
  _n1(n1),
  _n2(n2),
  _n3(nullptr),
  _symbol(symbol),
  _intValue(0),
  _token(nullptr)
{
}

Node::Node(NodeType tpe):
  _tpe(tpe),
  _type(Type::NoType),
  _n1(nullptr),
  _n2(nullptr),
  _n3(nullptr),
  _symbol(nullptr),
  _intValue(0),
  _token(nullptr)
{
}

Node::Node(NodeType tpe, unsigned intValue):
  _tpe(tpe),
  _type(Type::NoType),
  _n1(nullptr),
  _n2(nullptr),
  _n3(nullptr),
  _symbol(nullptr),
  _intValue(intValue),
  _token(nullptr)
{
}

Node::Node(NodeType tpe, Tokens::Token *token):
  _tpe(tpe),
  _type(Type::NoType),
  _n1(nullptr),
  _n2(nullptr),
  _n3(nullptr),
  _symbol(nullptr),
  _intValue(0),
  _token(token)
{
}

Node::~Node()
{
  if (_n1 != nullptr)
    delete _n1;
  if (_n2 != nullptr)
    delete _n2;
  if (_n3 != nullptr)
    delete _n3;
  if (_token != nullptr)
    delete _token;
}

Type Node::type()
{
  return _type;
}

void Node::setType(Type t)
{
  _type = t;
}

NodeType Node::tpe()
{
  return _tpe;
}

Node *Node::decl()
{
  switch (_tpe) {
    case Decls:
      return _n1;
    default:
      err("decl");
      return nullptr;
  }
}

Node *Node::decls()
{
  switch (_tpe) {
    case Prog:
      return _n1;
    default:
      err("decls");
      return nullptr;
  }
}

Node *Node::stmt()
{
  switch (_tpe) {
    case Statements:
      return _n1;
    case StatementWhile:
      return _n2;
    default:
      return nullptr;
  }
}

Node *Node::stmts()
{
  switch (_tpe) {
    case Prog:
      return _n2;
    case StatementBlock:
      return _n1;
    default:
      err("stmts");
      return nullptr;
  }
}

Node *Node::nextDecl()
{
  switch (_tpe) {
    case Decls:
      return _n2;
    default:
      err("nextDecl");
      return nullptr;
  }
}

Node *Node::nextStmt()
{
  switch (_tpe) {
    case Statements:
      return _n2;
    default:
      err("nextStmt");
      return nullptr;
  }
}

Node *Node::arr()
{
  switch (_tpe) {
    case DeclArray:
      return _n1;
    default:
      err("arr");
      return nullptr;
  }
}

Node *Node::exp()
{
  switch (_tpe) {
    case StatementIdent:
      return _n2;
    case StatementWrite:
      return _n1;
    case StatementIf:
      return _n1;
    case StatementWhile:
      return _n1;
    case Exp2:
      return _n1;
    case Index:
      return _n1;
    case OpExp:
      return _n2;
    default:
      err("exp");
      return nullptr;
  }
}

Node *Node::exp2()
{
  switch (_tpe) {
    case Exp:
      return _n1;
    case Exp2Minus:
      return _n1;
    case Exp2Neg:
      return _n1;
    default:
      err("exp2");
      return nullptr;
  }
}

Node *Node::op()
{
  switch (_tpe) {
    case Exp:
      return _n2;
    case OpExp:
      return _n1;
    default:
      err("op");
      return nullptr;
  }
}

Node *Node::index()
{
  switch (_tpe) {
    case StatementIdent:
      return _n1;
    case StatementRead:
      return _n1;
    case Exp2Ident:
      return _n1;
    default:
      err("index");
      return nullptr;
  }
}

Node *Node::ifStmt()
{
  switch (_tpe) {
    case StatementIf:
      return _n2;
    default:
      err("ifStmt");
      return nullptr;
  }
}

Node *Node::elseStmt()
{
  switch (_tpe) {
    case StatementIf:
      return _n3;
    default:
      err("elseStmt");
      return nullptr;
  }
}

Symbol *Node::symbol()
{
  switch (_tpe) {
    case DeclArray:
    case DeclIdent:
    case StatementIdent:
    case StatementRead:
    case Exp2Ident:
      return _symbol;
    default:
      err("symbol");
      return nullptr;
  }
}

unsigned Node::intValue()
{
  switch (_tpe) {
    case Array:
    case Exp2Int:
      return _intValue;
    default:
      err("intValue");
      return 0;
  }
}

Tokens::Token *Node::token()
{
  switch (_tpe) {
    case Op:
      return _token;
    default:
      err("token");
      return nullptr;
  }
}

const char *Node::tpeName()
{
  switch(_tpe) {
    case Prog:
      return "Prog";
    case Decls:
      return "Decls";
    case DeclArray:
      return "DeclArray";
    case DeclIdent:
      return "DeclIdent";
    case Array:
      return "Array";
    case Statements:
      return "Statements";
    case StatementIdent:
      return "StatementIdent";
    case StatementWrite:
      return "StatementWrite";
    case StatementRead:
      return "StatementRead";
    case StatementBlock:
      return "StatementBlock";
    case StatementIf:
      return "StatementIf";
    case StatementWhile:
      return "StatementWhile";
    case Exp:
      return "Exp";
    case Exp2:
      return "Exp2";
    case Exp2Ident:
      return "Exp2Ident";
    case Exp2Int:
      return "Exp2Int";
    case Exp2Minus:
      return "Exp2Minus";
    case Exp2Neg:
      return "Exp2Neg";
    case Index:
      return "Index";
    case OpExp:
      return "OpExp";
    case Op:
      return "Op";
    case Nil:
      return "Nil";
    default:
      // can't be reached
      return nullptr;
  }
}

void Node::err(const char *fnName)
{
  fprintf(stderr, "unsupported call of '%s' for node type %s\n",
      fnName, tpeName());
  exit(1);
}
