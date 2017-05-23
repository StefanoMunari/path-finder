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

SRC=$(shell find $(SRCDIR) -name *.cc)
OBJ=$(SRC:%.cc=%.o)
BIN=find_path

all: compile

%.o: %.cc
	@echo "\n=>Compiling: $@"
	$(CXX) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

preprocessing:
	@echo '' \
	$$(mv $(TRASHDIR)/*.o $(SRCDIR) 2>&-) >/dev/null

copy_to_obj: preprocessing $(OBJ)
	@echo '' \
	$$(cp $(OBJ) $(OBJDIR) ) >/dev/null

$(BINDIR)/$(BIN): copy_to_obj
	@echo "\n=>Linking: $(OBJDIR)/*.o"
	$(CXX) $(CFLAGS) $(OBJDIR)/*.o -o $@ -L$(LIBDIR) -l$(LIB)

compile: $(BINDIR)/$(BIN)
	@echo '' \
	$$(mv $(OBJ) $(TRASHDIR) ) >/dev/null

.PHONY: run
run: compile
	@echo "=>Running: $(BINDIR)/$(BIN)"
	$(BINDIR)/$(BIN) 2>&1 | tee -a make_run.log && rm make_run.log


.PHONY: clean
clean:
	find $(PWD) -type f -name "*.o" -delete