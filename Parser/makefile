
CC = g++
FLAGS = -W -Wall -Wextra -g -std=c++11
LIBFLAGS = -g -std=c++11
LINKS = -I../Automat/src -I../Buffer/src -I../Symboltable/src -I../Scanner/src -L../sharedlib -lBuffer -lAutomat -lSymboltable -lScanner

SRCDIR = src
OBJDIR = debug
BINDIR = debug
LIBDIR = lib
SHAREDLIB = ../sharedlib

OBJS = \
	$(OBJDIR)/Parser.o \
	$(OBJDIR)/TestParser.o

OBJSLIB = \
	$(LIBDIR)/Parser.o

# $^ liste der abhaengigkeiten
makeTestParser: $(OBJS)
	$(CC) $(FLAGS) $^ $(LINKS) -o $(BINDIR)/TestParser

# $@ name des object files
# $< erste abhaengigkeit
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(FLAGS) -c $(LINKS) -o $@ $<

clean:
	rm -rf $(OBJDIR)/*
	$(MAKE) testParser

# erstellen der shared library
ParserLib: $(OBJSLIB)
	$(CC) -shared -o $(SHAREDLIB)/libParser.so $^

$(LIBDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(LIBFLAGS) -c -fPIC $(LINKS) -o $@ $<
