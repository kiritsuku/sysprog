#ifndef Automat_H_
#define Automat_H_

#include "Token.h"

class Automat final {
public:
  explicit Automat();
  ~Automat();

  Tokens::Token accept(const char c);

private:
  class State {
  public:
    explicit State(Automat &outer);
    virtual ~State();
    virtual Tokens::Token accept(const char c) = 0;
  protected:
    Automat &outer;
  };

  class StartState final : public State {
  public:
    StartState(Automat &outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class IdentState final : public State {
  public:
    IdentState(Automat &outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class SignState final : public State {
  public:
    SignState(Automat &outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class SmallerState final : public State {
  public:
    SmallerState(Automat &outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class ColonState final : public State {
  public:
    ColonState(Automat &outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class IntState final : public State {
  public:
    IntState(Automat &outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class CommentState final : public State {
  public:
    CommentState(Automat &outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class CommentEndState final : public State {
  public:
    CommentEndState(Automat &outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class SmallerColonState final : public State {
  public:
    SmallerColonState(Automat &outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  class ColonEqualsState final : public State {
  public:
    ColonEqualsState(Automat &outer): State(outer) {}
    Tokens::Token accept(const char c) override;
  };

  StartState *const startState;
  IdentState *const identState;
  SignState *const signState;
  SmallerState *const smallerState;
  ColonState *const colonState;
  IntState *const intState;
  CommentState *const commentState;
  CommentEndState *const commentEndState;
  SmallerColonState *const smallerColonState;
  ColonEqualsState *const colonEqualsState;

  State *state;
};

#endif
