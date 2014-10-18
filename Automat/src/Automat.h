#ifndef Automat_H_
#define Automat_H_

#include "Token.h"

class Automat final {
public:
	explicit Automat():
    startState(*new StartState(*this)),
    identState(*new IdentState(*this)),
    signState(*new SignState(*this)),
    intState(*new IntState(*this)),
    commentState(*new CommentState(*this)),
    commentEndState(*new CommentEndState(*this)),
    smallerColonState(*new SmallerColonState(*this)),
    colonEqualsState(*new ColonEqualsState(*this)),
    state(startState)
  {}

	~Automat() {
    delete &startState;
    delete &identState;
    delete &signState;
    delete &intState;
    delete &commentState;
    delete &commentEndState;
    delete &smallerColonState;
    delete &colonEqualsState;
    delete &state;
  }

  Tokens::Token accept(const char c);

private:
  class State {
  public:
    virtual ~State() {
      delete &outer;
    }
    State(Automat& outer): outer(outer) {}
    virtual Tokens::Token accept(const char c) = 0;
    inline const State& operator=(const State& state) {
      // TODO why is this function needed?
      return state;
    }
  protected:
    Automat &outer;
  };

  class StartState final : public State {
  public:
    StartState(Automat& outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class IdentState final : public State {
  public:
    IdentState(Automat& outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class SignState final : public State {
  public:
    SignState(Automat& outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class IntState final : public State {
  public:
    IntState(Automat& outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class CommentState final : public State {
  public:
    CommentState(Automat& outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class CommentEndState final : public State {
  public:
    CommentEndState(Automat& outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class SmallerColonState final : public State {
  public:
    SmallerColonState(Automat& outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class ColonEqualsState final : public State {
  public:
    ColonEqualsState(Automat& outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  StartState &startState;
  IdentState &identState;
  SignState &signState;
  IntState &intState;
  CommentState &commentState;
  CommentEndState &commentEndState;
  SmallerColonState &smallerColonState;
  ColonEqualsState &colonEqualsState;

  unsigned char lastSign;
  State &state;
};

#endif
