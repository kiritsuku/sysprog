#ifndef TOKEN_H_
#define TOKEN_H_

#include <Symboltable.h>

class Tokens final {
public:
  class Token {
  public:
    explicit Token();
    virtual ~Token();
    virtual const char *text() = 0;
    virtual unsigned textLen();
    virtual bool isIdent();
    virtual bool isInt();
  };

  class NoneToken final : public Token {
  public:
    NoneToken(): Token() {}
    const char *text() override { return "<none>"; }
  };

  class IgnoreToken final : public Token {
  public:
    IgnoreToken(): Token() {}
    const char *text() override { return "<ignore>"; }
  };

  class ErrorToken final : public Token {
  public:
    ErrorToken(): Token() {}
    const char *text() override { return "<error>"; }
  };

  class EofToken final : public Token {
  public:
    EofToken(): Token() {}
    const char *text() override { return "<eof>"; }
  };

  class IntToken final : public Token {
  public:
    IntToken(): Token() {}
    const char *text() override { return "<int>"; }
  };

  class StrToken final : public Token {
  public:
    StrToken(): Token() {}
    const char *text() override { return "<str>"; }
  };

  class PlusToken final : public Token {
  public:
    PlusToken(): Token() {}
    const char *text() override { return "+"; }
  };

  class MinusToken final : public Token {
  public:
    MinusToken(): Token() {}
    const char *text() override { return "-"; }
  };

  class DivToken final : public Token {
  public:
    DivToken(): Token() {}
    const char *text() override { return "/"; }
  };

  class MulToken final : public Token {
  public:
    MulToken(): Token() {}
    const char *text() override { return "*"; }
  };

  class SmallerToken final : public Token {
  public:
    SmallerToken(): Token() {}
    const char *text() override { return "<"; }
  };

  class GreaterToken final : public Token {
  public:
    GreaterToken(): Token() {}
    const char *text() override { return ">"; }
  };

  class EqualsToken final : public Token {
  public:
    EqualsToken(): Token() {}
    const char *text() override { return "="; }
  };

  class ColonEqualsToken final : public Token {
  public:
    ColonEqualsToken(): Token() {}
    const char *text() override { return ":="; }
  };

  class SmallerColonGreaterToken final : public Token {
  public:
    SmallerColonGreaterToken(): Token() {}
    const char *text() override { return "<:>"; }
  };

  class BangToken final : public Token {
  public:
    BangToken(): Token() {}
    const char *text() override { return "!"; }
  };

  class AndToken final : public Token {
  public:
    AndToken(): Token() {}
    const char *text() override { return "&"; }
  };

  class SemiToken final : public Token {
  public:
    SemiToken(): Token() {}
    const char *text() override { return ";"; }
  };

  class LParenToken final : public Token {
  public:
    LParenToken(): Token() {}
    const char *text() override { return "("; }
  };

  class RParenToken final : public Token {
  public:
    RParenToken(): Token() {}
    const char *text() override { return ")"; }
  };

  class LBraceToken final : public Token {
  public:
    LBraceToken(): Token() {}
    const char *text() override { return "{"; }
  };

  class RBraceToken final : public Token {
  public:
    RBraceToken(): Token() {}
    const char *text() override { return "}"; }
  };

  class LBracketToken final : public Token {
  public:
    LBracketToken(): Token() {}
    const char *text() override { return "["; }
  };

  class RBracketToken final : public Token {
  public:
    RBracketToken(): Token() {}
    const char *text() override { return "]"; }
  };

  class IfToken final : public Token {
  public:
    IfToken(): Token() {}
    const char *text() override { return "if"; }
  };

  class WhileToken final : public Token {
  public:
    WhileToken(): Token() {}
    const char *text() override { return "while"; }
  };

  class IdentToken final : public Token {
  public:
    explicit IdentToken(unsigned pos, Symbol& sym);
    const char *text() override;
    bool isIdent() override;

    const unsigned pos;
    Symbol &sym;
  };

  class NumberToken final : public Token {
  public:
    explicit NumberToken(unsigned pos, unsigned value, char *strvalue);
    ~NumberToken() override;
    const char *text() override;
    bool isInt() override;

    const unsigned pos;
    const unsigned value;
  private:
    const char *strvalue;
  };

  static NoneToken *const None;
  static IgnoreToken *const Ignore;
  static ErrorToken *const Error;
  static EofToken *const Eof;
  static IntToken *const Int;
  static StrToken *const Str;
  static PlusToken *const Plus;
  static MinusToken *const Minus;
  static DivToken *const Div;
  static MulToken *const Mul;
  static SmallerToken *const Smaller;
  static GreaterToken *const Greater;
  static EqualsToken *const Equals;
  static ColonEqualsToken *const ColonEquals;
  static SmallerColonGreaterToken *const SmallerColonGreater;
  static BangToken *const Bang;
  static AndToken *const And;
  static SemiToken *const Semi;
  static LParenToken *const LParen;
  static RParenToken *const RParen;
  static LBraceToken *const LBrace;
  static RBraceToken *const RBrace;
  static LBracketToken *const LBracket;
  static RBracketToken *const RBracket;
  static IfToken *const If;
  static WhileToken *const While;

  static IdentToken *createIdent(unsigned pos, Symbol &sym);
  static NumberToken *createNumber(unsigned pos, unsigned value, char *strvalue);

  static Token *tokenOf(unsigned char c);

  /**
   * Checks if `text` is a keyword. If this is the case the corresponding
   * token is returned. Otherwise `Token::None` is returned.
   */
  static Token *keyword(const char *text);
};

#endif
