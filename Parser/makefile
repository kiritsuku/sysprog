
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
	$(OBJDIR)/Typer.o \
	$(OBJDIR)/Nodes.o \
	$(OBJDIR)/Parser.o \
	$(OBJDIR)/TestHelper.o

OBJSLIB = \
	$(OBJDIR)/Typer.o \
	$(OBJDIR)/Nodes.o \
	$(LIBDIR)/Parser.o

# $^ liste der abhaengigkeiten
testParser: $(OBJS) $(OBJDIR)/TestParser.o
	$(CC) $(FLAGS) $^ $(LINKS) -o $(BINDIR)/TestParser

testTyper: $(OBJS) $(OBJDIR)/TestTyper.o
	$(CC) $(FLAGS) $^ $(LINKS) -o $(BINDIR)/TestTyper

# $@ name des object files
# $< erste abhaengigkeit
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(FLAGS) -c $(LINKS) -o $@ $<

clean:
	rm -rf $(OBJDIR)/*
	$(MAKE) testParser
	$(MAKE) testTyper

# erstellen der shared library
ParserLib: $(OBJSLIB)
	$(CC) -shared -o $(SHAREDLIB)/libParser.so $^

$(LIBDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(LIBFLAGS) -c -fPIC $(LINKS) -o $@ $<
