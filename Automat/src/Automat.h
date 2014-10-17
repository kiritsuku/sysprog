#ifndef Automat_H_
#define Automat_H_

#include "Token.h"

class Automat final {
public:
	explicit Automat(): lastState(StartState::instance()) {}
	~Automat() {}

  Tokens::Token accept(const char c);

private:
  class State {
  public:
//    State(Automat& outer): outer(outer) {}
    virtual Tokens::Token accept(const char c) = 0;
 // private:
 //   Automat& outer;
  };
  class StartState final : public State {
  public:
    static StartState& instance() {
      static StartState ins;
      return ins;
    }
    Tokens::Token accept(const char c) override;
  };
  class IdentState final : public State {
  public:
    static IdentState& instance() {
      static IdentState ins;
      return ins;
    }
    Tokens::Token accept(const char c) override;
  };
  class SignState final : public State {
  public:
    static SignState& instance() {
      static SignState ins;
      return ins;
    }
    Tokens::Token accept(const char c) override;
  };
  class IntState final : public State {
  public:
    static IntState& instance() {
      static IntState ins;
      return ins;
    }
    Tokens::Token accept(const char c) override;
  };

  Tokens::Token switchState(State& newState, Tokens::Token newToken);

  unsigned acceptedSigns;
  Tokens::Token lastToken;
  State& lastState;
};

#endif
