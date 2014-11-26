# Definition der Variablen

CC = g++
FLAGS = -W -Wall -Wextra -g -std=c++11 -O2
LIBFLAGS = -g -std=c++11 -O2

SRCDIR = src
OBJDIR = debug
BINDIR = debug
LIBDIR = lib

SHAREDLIB = ../sharedlib

#
#		Targets zum Bauen des Tests
#

# Linken der Object-files
makeTestBuffer: BufferTarget TestBufferTarget
	$(CC) $(FLAGS) $(OBJDIR)/Buffer.o $(OBJDIR)/TestBuffer.o -o $(BINDIR)/BufferTest

# compilieren der Source-files
# Buffer.o ist abhaengig von Buffer.cpp und Buffer.h
BufferTarget:  $(SRCDIR)/Buffer.cpp $(SRCDIR)/Buffer.h
	$(CC) $(FLAGS) -c -o $(OBJDIR)/Buffer.o $(SRCDIR)/Buffer.cpp

#TestBuffer.o ist abhaengig von TestBuffer.cpp und Buffer.h
TestBufferTarget:  $(SRCDIR)/TestBuffer.cpp $(SRCDIR)/Buffer.h
	$(CC) $(FLAGS) -c -o $(OBJDIR)/TestBuffer.o $(SRCDIR)/TestBuffer.cpp

# loeschen aller files im verzeichnis $(OBJDIR) und$(LIBDIR) und neu bauen
cleanBuffer:
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*
	$(MAKE) makeTestBuffer

#
# erstellen der shared library
#
BufferLib: BufferLibTarget
	$(CC) -shared  -o $(SHAREDLIB)/libBuffer.so $(LIBDIR)/Buffer.o

BufferLibTarget: $(SRCDIR)/Buffer.cpp $(SRCDIR)/Buffer.h
	$(CC) $(LIBFLAGS) -c -fPIC  -o $(LIBDIR)/Buffer.o  $(SRCDIR)/Buffer.cpp


