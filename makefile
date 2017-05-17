CXX=g++
CFLAGS=-std=c++17 -Wall -Werror
CVG=
CDBG=

SRCDIR=$(PWD)/src
OBJDIR=$(PWD)/obj
BINDIR=$(PWD)/bin
TRASHDIR=$(SRCDIR)/_trash
LIBDIR=/usr/include
LIB=python2.7
INCLUDE=/usr/include/boost

SRC=$(wildcard $(SRCDIR)/*.cc)
OBJ=$(SRC:%.cc=%.o)
BIN=find_path

all: compile

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@echo "=>Compiling: $@" \
	$(CXX) $(CFLAGS) -I $(INCLUDE) -c $@ $<

preprocessing:
	@echo '' \
	$$(mv $(TRASHDIR)/*.o $(SRCDIR) 2>&-) >/dev/null

copy_to_obj: preprocessing $(OBJ)
	@echo '' \
	$$(cp $(SRCDIR)/*.o $(OBJDIR) ) >/dev/null

$(BINDIR)/$(BIN): copy_to_obj
	@echo "=>Linking: $(OBJDIR)/*.o"
	$(CXX) $(CFLAGS) $(OBJDIR)/*.o -o $@ -L$(LIBDIR) -l$(LIB)

compile: $(BINDIR)/$(BIN)
	@echo '' \
	$$(mv $(SRCDIR)/*.o $(TRASHDIR) ) >/dev/null

.PHONY: run
run: compile
	@echo "=>Running: $(BINDIR)/$(BIN)"
	$(BINDIR)/$(BIN) 2>&1 | tee -a make_run.log && rm make_run.log


.PHONY: clean
clean:
	rm -rf $(OBJDIR)/*.o $(TRASHDIR)/*.o $(SRCDIR)/*.o