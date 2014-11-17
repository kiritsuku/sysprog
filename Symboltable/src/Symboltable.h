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
   * Creates a symbol that represents `str` if it does not yet exist or
   * returns the already existing symbol.
   */
  Symbol *create(char *str);

private:
  unsigned tableSize;
  unsigned existingElements;
  Symbol **data;

  unsigned long strhash(const char *str, const unsigned offset = 0);
  unsigned indexOf(const char *str);
  bool isFull();
  void resize();
  void resizeCreate(Symbol *sym);
};

#endif
