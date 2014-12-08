AUTOMATDIR = Automat
BUFFERDIR = Buffer
SYMBOLTABLEDIR = Symboltable
SCANNERDIR = Scanner
PARSERDIR = Parser
SHAREDLIB = sharedlib

MKDIR = mkdir -p

all: directories bufferLib symboltableLib automatLib scannerLib scanner parser
	@echo "build all"

directories:
	$(MKDIR) $(AUTOMATDIR)/lib
	$(MKDIR) $(AUTOMATDIR)/debug
	$(MKDIR) $(BUFFERDIR)/lib
	$(MKDIR) $(BUFFERDIR)/debug
	$(MKDIR) $(SYMBOLTABLEDIR)/lib
	$(MKDIR) $(SYMBOLTABLEDIR)/debug
	$(MKDIR) $(SCANNERDIR)/lib
	$(MKDIR) $(SCANNERDIR)/debug
	$(MKDIR) $(PARSERDIR)/lib
	$(MKDIR) $(PARSERDIR)/debug
	$(MKDIR) $(SHAREDLIB)

clean:
	rm -rf $(AUTOMATDIR)/lib/*
	rm -rf $(AUTOMATDIR)/debug/*
	rm -rf $(BUFFERDIR)/lib/*
	rm -rf $(BUFFERDIR)/debug/*
	rm -rf $(SYMBOLTABLEDIR)/lib/*
	rm -rf $(SYMBOLTABLEDIR)/debug/*
	rm -rf $(SCANNERDIR)/lib/*
	rm -rf $(SCANNERDIR)/debug/*
	rm -rf $(PARSERDIR)/lib/*
	rm -rf $(PARSERDIR)/debug/*
	rm -rf $(SHAREDLIB)/*
	$(MAKE) all

parser:
	$(MAKE) -C $(PARSERDIR) testParser testTyper

scanner:
	$(MAKE) -C $(SCANNERDIR) makeTestScanner

automatLib:
	$(MAKE) -C $(AUTOMATDIR) AutomatLib

bufferLib:
	$(MAKE) -C $(BUFFERDIR) BufferLib

scannerLib:
	$(MAKE) -C $(SCANNERDIR) ScannerLib

symboltableLib:
	$(MAKE) -C $(SYMBOLTABLEDIR) SymboltableLib
