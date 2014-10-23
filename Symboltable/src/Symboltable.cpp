#include <string.h>
#include "Symboltable.h"

Symboltable::Symboltable():
  tableSize(64),
  data(new Symbol*[tableSize])
{
  memset(data, 0, sizeof(Symbol*)*tableSize);
}

Symboltable::~Symboltable()
{
  for (unsigned i = 0; i < tableSize; ++i) {
    auto sym = data[i];
    if (sym != nullptr)
      delete sym;
  }
  delete[] data;
}

Symbol *Symboltable::create(char *str)
{
  auto i = indexOf(str);

  if (data[i] == nullptr) {
    Symbol *sym = new Symbol(str);
    data[i] = sym;
    return sym;
  }
  else
    return data[i];
}

unsigned Symboltable::indexOf(char *str)
{
  auto h = strhash(str);
  unsigned i = 0;
  while (data[h] != nullptr && strcmp(data[h]->ident, str) != 0)
    h = strhash(str, i++);
  return h;
}

unsigned long Symboltable::strhash(char *str, unsigned offset)
{
  // implementation from http://www.cse.yorku.ca/~oz/hash.html
  unsigned long h = 5381;
  int c;
  while ((c = *str++))
    h = ((h << 5)+h)+c+offset;
  return h % tableSize;
}

Symbol::Symbol(char const *ident)
{
  auto len = strlen(ident);
  this->ident = new char[len+1];
  strcpy((char*) this->ident, ident);
}

Symbol::~Symbol()
{
  delete[] ident;
}
