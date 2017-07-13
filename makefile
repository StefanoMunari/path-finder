CXX=g++
CFLAGS=-std=c++17 -Wall -pthread $(CDBG) $(CVGD)
# -Werror
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
	$(CXX) $(CFLAGS) $(CVG) -I $(INCLUDE) -c $< -o $@

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
	$(BINDIR)/$(BIN) $(ARGS)

.PHONY: profile
profile: compile
	@echo "=>Profiled: $(BINDIR)/$(BIN)"
	valgrind $(VGDOPTS) $(BINDIR)/$(BIN) 2>&1 | tee -a make_run.log && rm make_run.log

.PHONY: help
help:
	@echo "Usage: make [commands] [options]\n"\
		"Options:\n"\
		"\t ARGS=<arg_list>\t\t\t\t  Runs with the argument list for main process.\n"\
		"\t CDBG=-DDEBUG=1\t\t\t\t  Compiles with the debugging flag activated.\n"\
		"\t CVGD=-g\t\t\t\t\t  Compiles with the valgrind flag activated.\n"\
		"\t VGDOPTS=<valgrind_options>\t  Execs with the defined options for valgrind (only in profile mode).\n"\
		"\n"\
		"Commands:\n" \
		"\t {compile, run, profile, clean, help}\n"


.PHONY: clean
clean:
	@echo ""\
	$$(find $(PWD) -type f -name "*.o" -delete) >/dev/null
	@echo "=>Cleaned object files"