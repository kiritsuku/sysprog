
CC = g++
FLAGS = -W -Wall -Wextra -g -std=c++11 -O2
LIBFLAGS = -g -std=c++11 -O2
LINKS = -I../Automat/src -I../Buffer/src -I../Symboltable/src -L../sharedlib -lAutomat -lBuffer -lSymboltable

SRCDIR = src
OBJDIR = debug
BINDIR = debug
LIBDIR = lib
SHAREDLIB = ../sharedlib

## hier alle Object Files eintragen
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Scanner.o \
	$(OBJDIR)/TestScanner.o \
	$(OBJDIR)/ErrorHandler.o

OBJSFORSCANNERLIB =  \
	$(LIBDIR)/Scanner.o



# Variante mit wenig Makefile-Kenntnissen

# linken der Object-files under shared libraries
#makeTestScanner: $(OBJDIR)/Scanner.o $(OBJDIR)/TestScanner.o
#	g++ -g $(OBJDIR)/Scanner.o $(OBJDIR)/TestScanner.o -L../sharedlib  -lAutomat  -lBuffer -lSymboltable -o $(BINDIR)/ScannerTest
#
#
#
## compilieren der source-files
#$(OBJDIR)/Scanner.o :  $(SRCDIR)/Scanner.cpp
#	@echo "g++ $*.cpp"
#	g++ -g  -c -Wall  -o $(OBJDIR)/Scanner.o  $(SRCDIR)/Scanner.cpp
#
#$(OBJDIR)/TestScanner.o :  $(SRCDIR)/TestScanner.cpp
#	@echo "g++ $*.cpp"
#	g++ -g  -c -Wall  -o $(OBJDIR)/TestScanner.o  $(SRCDIR)/TestScanner.cpp
#



# Variante  mit guten Kenntnissen
# $^ liste der abhaengigkeiten
makeTestScanner: $(OBJS)
	$(CC) $(FLAGS) $^ $(LINKS) -o $(BINDIR)/ScannerTest

# $@ name des object files
# $< erste abhaengigkeit
$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp
	$(CC) $(FLAGS) -c $(LINKS) -o $@  $<

# loeschen aller files im verzeichnis $(OBJDIR) und $(LIBDIR) und neu bauen
cleanScanner:
	rm -rf $(OBJDIR)/*
	$(MAKE) makeTestScanner

## erstellen der shared library
ScannerLib: $(OBJSFORSCANNERLIB)
	$(CC) -shared -o $(SHAREDLIB)/libScanner.so $^

$(LIBDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(LIBFLAGS) -c -fPIC $(LINKS) -o $@ $<
