#include "Automat.h"

#ifndef OUTERCLASS
#define OUTERCLASS(className, memberName) \
    reinterpret_cast<className*>(reinterpret_cast<unsigned char*>(this) - offsetof(className, memberName))
#endif

Tokens::Token Automat::StartState::accept(const char c)
{
  (void) c;
  return Tokens::None;
}

Tokens::Token Automat::IdentState::accept(const char c)
{
  Tokens::Token token;
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
      break;
    default:
//      token = this->switchState(StartState::instance(), Tokens::Ident);
      break;
  }
  return Tokens::None;
}

Tokens::Token Automat::SignState::accept(const char c)
{
  (void) c;
  return Tokens::None;
}

Tokens::Token Automat::IntState::accept(const char c)
{
  (void) c;
  return Tokens::None;
}

Tokens::Token Automat::switchState(Automat::State& newState, Tokens::Token newToken)
{
  if (&lastState != &newState) {
    lastState = newState;
    acceptedSigns = 1;
    auto t = lastToken;
    lastToken = newToken;
    return t;
  }
  else {
    acceptedSigns += 1;
    return Tokens::None;
  }
}

Tokens::Token Automat::accept(const char c)
{
  lastState.accept(c);
  Tokens::Token token;
  switch(c) {
    case ' ': case '\t':
      token = switchState(StartState::instance(), Tokens::Ignore);
      break;
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
      token = switchState(IdentState::instance(), Tokens::Ident);
      break;

    case '0': case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9':
      token = switchState(IntState::instance(), Tokens::Int);
      break;

    case '+':
      token = switchState(SignState::instance(), Tokens::Plus);
      break;

    case '-':
      token = switchState(SignState::instance(), Tokens::Minus);
      break;

    case '/':
      break;

    case '*':
      break;

    case '<':
      break;

    case '>':
      break;

    case '=':
      break;

    case ':':
      break;

    case '!':
      break;

    case '&':
      break;

    case ';':
      break;

    case '(':
      break;

    case ')':
      break;

    case '{':
      break;

    case '}':
      break;

    case '[':
      break;

    case ']':
      break;
  }
  return token;
}
