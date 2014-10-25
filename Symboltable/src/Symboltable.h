#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

class Symbol final {
public:
  explicit Symbol(char const *ident);
  ~Symbol();

  /**
   * The identifier represented by this symbol.
   */
  char const *ident;
};

class Symboltable final {
public:
  explicit Symboltable();
  ~Symboltable();

  /**
   * Creates a symbol to `str` if it does not yet exists and returns a
   * reference to it.
   */
  Symbol *create(char *str);

private:
  unsigned tableSize;
  Symbol **data;
  unsigned long strhash(char *str, unsigned offset = 0);
  unsigned indexOf(char *str);
};

#endif
