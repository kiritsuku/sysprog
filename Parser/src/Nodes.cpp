#include "Nodes.h"

using namespace Nodes;

Node::Node(NodeType _tpe, Node *_decls, Node *_stmts):
  _tpe(_tpe),
  _decls(_decls),
  _stmts(_stmts),
  _nextDecl(nullptr),
  _arr(nullptr),
  _name(nullptr),
  _size(0)
{
}

Node::Node(NodeType _tpe, Node *_nextDecl):
  _tpe(_tpe),
  _decls(nullptr),
  _stmts(nullptr),
  _nextDecl(_nextDecl),
  _arr(nullptr),
  _name(nullptr),
  _size(0)
{
}

Node::Node(NodeType _tpe, Node *_arr, Symbol *_name):
  _tpe(_tpe),
  _decls(nullptr),
  _stmts(nullptr),
  _nextDecl(nullptr),
  _arr(_arr),
  _name(_name),
  _size(0)
{
}

Node::Node(NodeType _tpe, Symbol *_name):
  _tpe(_tpe),
  _decls(nullptr),
  _stmts(nullptr),
  _nextDecl(nullptr),
  _arr(nullptr),
  _name(_name),
  _size(0)
{
}

Node::Node(NodeType _tpe, unsigned _size):
  _tpe(_tpe),
  _decls(nullptr),
  _stmts(nullptr),
  _nextDecl(nullptr),
  _arr(nullptr),
  _name(nullptr),
  _size(_size)
{
}

Node::Node(NodeType _tpe):
  _tpe(_tpe),
  _decls(nullptr),
  _stmts(nullptr),
  _nextDecl(nullptr),
  _arr(nullptr),
  _name(nullptr),
  _size(0)
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
