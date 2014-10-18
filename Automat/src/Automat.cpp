#include "Automat.h"

Tokens::Token Automat::StartState::accept(const char c)
{
  switch(c) {
    case ' ': case '\t':
      return Tokens::Ignore;
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
    case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
    case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
    case 's': case 't': case 'u': case 'v': case 'w': case 'x':
    case 'y': case 'z':
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
    case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
    case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
    case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
    case 'Y': case 'Z':
      outer.state = outer.identState;
      return Tokens::None;

    case '0': case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9':
      outer.state = outer.intState;
      return Tokens::None;

    case '<':
      outer.state = outer.smallerState;
      return Tokens::None;

    case ':':
      outer.state = outer.colonState;
      return Tokens::None;

    case '+': case '-': case '/': case '*': case '>': case '=':
    case '!': case '&': case ';': case '(': case ')': case '{':
    case '}': case '[': case ']':
      outer.state = outer.signState;
      return Tokens::None;

    default:
      return Tokens::Error;
  }
}

Tokens::Token Automat::IdentState::accept(const char c)
{
  switch(c) {
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
    case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
    case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
    case 's': case 't': case 'u': case 'v': case 'w': case 'x':
    case 'y': case 'z':
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
    case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
    case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
    case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
    case 'Y': case 'Z':
    case '0': case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9':
      return Tokens::None;

    default:
      outer.state = outer.startState;
      return Tokens::Ident;
  }
}

Tokens::Token Automat::SignState::accept(const char c)
{
  switch(c) {
    case '*':
      outer.state = outer.commentState;
      return Tokens::Ignore;
    default:
      outer.state = outer.startState;
      return Tokens::tokenOf(c);
  }
}

Tokens::Token Automat::SmallerState::accept(const char c)
{
  switch(c) {
    case ':':
      outer.state = outer.smallerColonState;
      return Tokens::None;
    default:
      outer.state = outer.startState;
      return Tokens::Smaller;
  }
}

Tokens::Token Automat::ColonState::accept(const char c)
{
  switch(c) {
    case '=':
      outer.state = outer.colonEqualsState;
      return Tokens::None;
    default:
      outer.state = outer.startState;
      return Tokens::Error;
  }
}

Tokens::Token Automat::IntState::accept(const char c)
{
  switch(c) {
    case '0': case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9':
      return Tokens::None;
    default:
      outer.state = outer.startState;
      return Tokens::Int;
  }
}

Tokens::Token Automat::CommentState::accept(const char c)
{
  switch(c) {
    case '*':
      outer.state = outer.commentEndState;
      return Tokens::Ignore;
    default:
      return Tokens::None;
  }
}

Tokens::Token Automat::CommentEndState::accept(const char c)
{
  switch(c) {
    case '/':
      outer.state = outer.startState;
    default:
      outer.state = outer.commentState;
  }
  return Tokens::Ignore;
}

Tokens::Token Automat::SmallerColonState::accept(const char c)
{
  switch(c) {
    case '=':
      outer.state = outer.colonEqualsState;
      return Tokens::Smaller;
    case '>':
      outer.state = outer.startState;
      return Tokens::SmallerColonGreater;
    default:
      outer.state = outer.startState;
      return Tokens::Error;
  }
}

Tokens::Token Automat::ColonEqualsState::accept(const char c)
{
  (void) c;
  outer.state = outer.startState;
  return Tokens::ColonEquals;
}

Tokens::Token Automat::accept(const char c)
{
  return state.accept(c);
}
