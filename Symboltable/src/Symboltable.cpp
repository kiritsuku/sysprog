#include <string.h>
#include "Symboltable.h"

Symboltable::Symboltable():
  tableSize(64),
  existingElements(0),
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
  if (isFull())
    resize();

  auto i = indexOf(str);

  if (data[i] == nullptr) {
    Symbol *sym = new Symbol(str);
    data[i] = sym;
    existingElements += 1;
    return sym;
  }
  else
    return data[i];
}

unsigned Symboltable::indexOf(const char *str)
{
  auto h = strhash(str);
  unsigned i = 0;
  while (data[h] != nullptr && strcmp(data[h]->ident, str) != 0)
    h = strhash(str, i++);
  return h;
}

unsigned long Symboltable::strhash(const char *str, const unsigned offset)
{
  // implementation from http://www.cse.yorku.ca/~oz/hash.html
  unsigned long h = 5381;
  int c;
  while ((c = *str++))
    h = ((h << 5)+h)+c+offset;
  return h % tableSize;
}

bool Symboltable::isFull()
{
  return existingElements >= tableSize*0.8;
}

void Symboltable::resize()
{
  auto oldData = data;
  auto oldSize = tableSize;
  tableSize *= 2;
  data = new Symbol*[tableSize];
  memset(data, 0, sizeof(Symbol*)*tableSize);

  for (unsigned i = 0; i < oldSize; ++i) {
    auto sym = oldData[i];
    if (sym != nullptr)
      resizeCreate(sym);
  }
  delete[] oldData;
}

void Symboltable::resizeCreate(Symbol *sym)
{
  auto i = indexOf(sym->ident);
  data[i] = sym;
}

Symbol::Symbol(char const *ident):
  _type(Type::NoType)
{
  auto len = strlen(ident);
  this->ident = new char[len+1];
  strcpy((char*) this->ident, ident);
}

Symbol::~Symbol()
{
  delete[] ident;
}

Type Symbol::type()
{
  return _type;
}

void Symbol::setType(Type t)
{
  _type = t;
}
