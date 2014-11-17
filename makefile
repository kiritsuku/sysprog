#
#	baut das komplette Scanner Projekt
#


AUTOMATDIR = Automat
BUFFERDIR = Buffer
SYMBOLTABLEDIR = Symboltable
SCANNERDIR = Scanner
SHAREDLIB = sharedlib

MKDIR = mkdir -p

all: directories bufferLib symboltableLib automatLib scanner
	@echo "target all"

directories:
	$(MKDIR) $(AUTOMATDIR)/lib
	$(MKDIR) $(AUTOMATDIR)/debug
	$(MKDIR) $(BUFFERDIR)/lib
	$(MKDIR) $(BUFFERDIR)/debug
	$(MKDIR) $(SYMBOLTABLEDIR)/lib
	$(MKDIR) $(SYMBOLTABLEDIR)/debug
	$(MKDIR) $(SCANNERDIR)/lib
	$(MKDIR) $(SCANNERDIR)/debug
	$(MKDIR) $(SHAREDLIB)


clean:
	rm -rf $(AUTOMATDIR)/lib/*
	rm -rf $(BUFFERDIR)/lib/*
	rm -rf $(SYMBOLTABLEDIR)/lib/*
	rm -rf $(SHAREDLIB)/*
	rm -rf $(SCANNERDIR)/debug/*
	$(MAKE) all


scanner:
	$(MAKE) -C $(SCANNERDIR) makeTestScanner

automatLib:
	$(MAKE) -C $(AUTOMATDIR) AutomatLib

bufferLib:
	$(MAKE) -C $(BUFFERDIR) BufferLib

# scannerLib wird erst fuer den Parser Teil benoetigt
#scannerLib:
#	$(MAKE) -C $(SCANNERDIR) ScannerLib

symboltableLib:
	$(MAKE) -C $(SYMBOLTABLEDIR) SymboltableLib
