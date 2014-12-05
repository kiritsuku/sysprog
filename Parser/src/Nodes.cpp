#include "Nodes.h"

using namespace Nodes;

Node::Node(NodeType _tpe, Node *_decls, Node *_stmts):
  _tpe(_tpe),
  _decls(_decls),
  _stmts(_stmts),
  _nextDecl(nullptr),
  _arr(nullptr),
  _name(nullptr),
  _size(0),
  _token(nullptr)
{
}

Node::Node(NodeType _tpe, Node *_nextDecl):
  _tpe(_tpe),
  _decls(nullptr),
  _stmts(nullptr),
  _nextDecl(_nextDecl),
  _arr(nullptr),
  _name(nullptr),
  _size(0),
  _token(nullptr)
{
}

Node::Node(NodeType _tpe, Node *_arr, Symbol *_name):
  _tpe(_tpe),
  _decls(nullptr),
  _stmts(nullptr),
  _nextDecl(nullptr),
  _arr(_arr),
  _name(_name),
  _size(0),
  _token(nullptr)
{
}

Node::Node(NodeType _tpe, Symbol *_name):
  _tpe(_tpe),
  _decls(nullptr),
  _stmts(nullptr),
  _nextDecl(nullptr),
  _arr(nullptr),
  _name(_name),
  _size(0),
  _token(nullptr)
{
}

Node::Node(NodeType _tpe, unsigned _size):
  _tpe(_tpe),
  _decls(nullptr),
  _stmts(nullptr),
  _nextDecl(nullptr),
  _arr(nullptr),
  _name(nullptr),
  _size(_size),
  _token(nullptr)
{
}

Node::Node(NodeType _tpe):
  _tpe(_tpe),
  _decls(nullptr),
  _stmts(nullptr),
  _nextDecl(nullptr),
  _arr(nullptr),
  _name(nullptr),
  _size(0),
  _token(nullptr)
{
}

Node::Node(NodeType _tpe, Tokens::Token *_token):
  _tpe(_tpe),
  _decls(nullptr),
  _stmts(nullptr),
  _nextDecl(nullptr),
  _arr(nullptr),
  _name(nullptr),
  _size(0),
  _token(_token)
{
}

Node::Node(NodeType _tpe, Symbol *_ident, Node *_idx, Node *_exp):
  _tpe(_tpe),
  _decls(_idx),
  _stmts(_exp),
  _nextDecl(nullptr),
  _arr(nullptr),
  _name(_ident),
  _size(0),
  _token(nullptr)
{
}

Node::Node(NodeType _tpe, Node *_exp, Node *_ifStmt, Node *_elseStmt):
  _tpe(_tpe),
  _decls(_exp),
  _stmts(_ifStmt),
  _nextDecl(_elseStmt),
  _arr(nullptr),
  _name(nullptr),
  _size(0),
  _token(nullptr)
{
}

NodeType Node::tpe()
{
  return _tpe;
}

Node *Node::decls()
{
  return _decls;
}

Node *Node::stmts()
{
  return _stmts;
}

Node *Node::nextDecl()
{
  return _nextDecl;
}

Node *Node::arr()
{
  return _arr;
}
