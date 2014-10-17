#ifndef Automat_H_
#define Automat_H_

#include "Token.h"

class Automat final {
public:
	explicit Automat():
    startState(*new StartState(*this)),
    lastState(startState)
  {}

	~Automat() {
    delete &startState;
    delete &lastState;
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

  Tokens::Token switchState(State &newState, Tokens::Token newToken);

  StartState &startState;

  unsigned acceptedSigns;
  Tokens::Token lastToken;
  State &lastState;
};

#endif
