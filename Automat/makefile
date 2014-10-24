#
#		Targets zum Bauen des Tests
#
CC = g++
FLAGS = -W -Wall -Wextra -g -std=c++11
LIBFLAGS = -g -std=c++11

# Linken der Object-files, abhaengig von AutomatTarget und TestAutomatTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestAutomat: TokenTarget AutomatTarget TestAutomatTarget
	$(CC) $(FLAGS) -I../Symboltable/src -L../sharedlib -lSymboltable debug/Automat.o debug/TestAutomat.o debug/Token.o -o debug/AutomatTest


# compilieren des Files Automat.cpp zu Automat.o,
# das Objekt-File ist abhängig von src/Automat.cpp und src/Automat.h
# flag:
# -c --> compilieren
# -Wall --> alle meldungen erzeugen

AutomatTarget: src/Automat.cpp src/Automat.h
	$(CC) $(FLAGS) -I../Symboltable/src -L../sharedlib -lSymboltable -c src/Automat.cpp -o debug/Automat.o


# TestAutomat.o ist abhängig von src/TestAutomat.cpp und src/Automat.h
TestAutomatTarget: src/TestAutomat.cpp src/Automat.h
	$(CC) $(FLAGS) -I../Symboltable/src -L../sharedlib -lSymboltable -c src/TestAutomat.cpp  -o debug/TestAutomat.o

TokenTarget: src/Token.cpp src/Token.h
	$(CC) $(FLAGS) -I../Symboltable/src -L../sharedlib -lSymboltable -c src/Token.cpp -o debug/Token.o

# loeschen aller files im verzeichnis obj und lib und neu bauen

cleanAutomat:
	rm -rf obj/*
	rm -rf lib/*
	$(MAKE) makeTestAutomat


#
# erstellen der shared library
#

AutomatLib: TokenLibTarget AutomatLibTarget
	$(CC) -shared lib/Token.o lib/Automat.o  -o ../sharedlib/libAutomat.so


# compilieren des Files Automat.cpp zu Automat.o mit dem Flag -fPIC (Position Independant Code)
AutomatLibTarget: src/Automat.cpp src/Automat.h
	$(CC) $(LIBFLAGS) -I../Symboltable/src -L../sharedlib -lSymboltable -c -fPIC src/Automat.cpp -o lib/Automat.o

TokenLibTarget: src/Token.cpp src/Token.h
	$(CC) $(LIBFLAGS) -I../Symboltable/src -L../sharedlib -lSymboltable -c -fPIC src/Token.cpp -o lib/Token.o



